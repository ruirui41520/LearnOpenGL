#include "model.h"

Model::Model(QString path, QOpenGLFunctions_3_3_Core *glFunctions) {
    m_functions = glFunctions;
    loadModel(path);
}

void Model::draw(QOpenGLShaderProgram *shader) {
  for (int i = 0; i < m_meshes.size(); i++) {
    m_meshes[i].draw(shader);
  }
}

void Model::loadModel(QString path) {
  Assimp::Importer m_importer;
  const aiScene *m_scene = m_importer.ReadFile(
      path.toStdString(), aiProcess_Triangulate | aiProcess_FlipUVs);
  if (!m_scene || m_scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
      !m_scene->mRootNode) {
    qWarning() << "error:load path failed";
    return;
  }
  directory = path.mid(0, path.lastIndexOf('/'));
  processNode(m_scene->mRootNode, m_scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh *m_mesh = scene->mMeshes[i];
    m_meshes.push_back(processMash(m_mesh, scene));
  }
  for (uint i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene);
  }
}

Mash Model::processMash(aiMesh *mesh, const aiScene *scene) {
  QVector<Vertex> vertices;
  QVector<uint> indices;
  QVector<Texture> textures;
  for (uint i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    QVector3D vector(mesh->mVertices[i].x, mesh->mVertices[i].y,
                     mesh->mVertices[i].z);
    vertex.Position = vector;
    QVector3D norVector(mesh->mNormals[i].x, mesh->mNormals[i].y,
                        mesh->mNormals[i].z);
    vertex.Normal = norVector;
    if (mesh->mTextureCoords[0]) {
      QVector2D texVec(mesh->mTextureCoords[0][i].x,
                       mesh->mTextureCoords[0][i].y);
      vertex.TexCoords = texVec;
    } else {
      vertex.TexCoords = QVector2D(0.0f, 0.0f);
    }
    vertices.push_back(vertex);
  }
  for (uint i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    indices.push_back(face.mIndices[i]);
  }
  if (mesh->mMaterialIndex >= 0) {
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    QVector<Texture> diffuseMaps = loadMaterialTextures(
        material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.append(diffuseMaps);
    QVector<Texture> specularMaps = loadMaterialTextures(
        material, aiTextureType_SPECULAR, "texture_specular");
    textures.append(specularMaps);
  }
  return Mash(vertices, indices, textures);
}

QVector<Texture> Model::loadMaterialTextures(aiMaterial *mat,
                                             aiTextureType type,
                                             QString typeName) {
  QVector<Texture> textures;
  for (uint i = 0; i < mat->GetTextureCount(type); i++) {
    aiString str;
    bool skip = false;
    mat->GetTexture(type, i, &str);
    for (int j = 0; j < texture_loaded.size(); j++) {
      if (std::strcmp(texture_loaded.at(j).path.toStdString().c_str(),
                      str.C_Str()) == 0) {
        textures.push_back(texture_loaded.at(j));
        skip = true;
        break;
      }
    }
    if (!skip) {
      Texture texture;
      texture.id = TextureFromFile(str.C_Str(), directory);
      texture.type = typeName;
      texture.path = QString(QLatin1String(str.C_Str()));
      textures.push_back(texture);
      texture_loaded.push_back(texture);
    }
  }
  return textures;
}

GLuint Model::TextureFromFile(const char *name, const QString &directory,
                              bool gamma) {
  Q_UNUSED(gamma);
  QString filename = QString(name);
  QString file = directory + "/" + filename;
  GLuint textureId;
  m_functions->glGenTextures(1, &textureId);
  QImage image;
  image.load(file);
  if (!image.isNull()) {
    m_functions->glBindTexture(GL_TEXTURE_2D, textureId);
    m_functions->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(),
                              image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                              image.bits());
    m_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    m_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    m_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                                 GL_LINEAR);
    m_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                                 GL_LINEAR);
    m_functions->glGenerateMipmap(GL_TEXTURE_2D);
  }
  return textureId;
}
