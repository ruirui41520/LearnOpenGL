#include "model.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Model::Model(QString path) { loadModel(path); }

void Model::draw(Shader *shader) {
  for (int i = 0; i < m_meshes.size(); i++) {
    m_meshes[i].draw(shader);
  }
}

void Model::loadModel(QString path) {
  Assimp::Importer m_importer;
  const aiScene *m_scene = m_importer.ReadFile(
      path.toStdString(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
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
    aiMesh *m_mesh = scene->mMeshes[node->mMeshes[i]];
    m_meshes.push_back(processMash(m_mesh, scene));
  }
  for (uint i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene);
  }
}

Mash Model::processMash(aiMesh *mesh, const aiScene *scene) {
  QVector<Vertex> vertices;
  QVector<uint> indices;
  std::vector<Texture> textures;
  for (uint i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    QVector3D vector;
    vector.setX(mesh->mVertices[i].x);
    vector.setY(mesh->mVertices[i].y);
    vector.setZ(mesh->mVertices[i].z);
    vertex.Position = vector;
    if (mesh->HasNormals()) {
      vector.setX(mesh->mNormals[i].x);
      vector.setY(mesh->mNormals[i].y);
      vector.setZ(mesh->mNormals[i].z);
      vertex.Normal = vector;
    }
    if (mesh->mTextureCoords[0]) {
      QVector2D texVec;
      texVec.setX(mesh->mTextureCoords[0][i].x);
      texVec.setY(mesh->mTextureCoords[0][i].y);
      vertex.TexCoords = texVec;
      vector.setX(mesh->mTangents[i].x);
      vector.setY(mesh->mTangents[i].y);
      vector.setZ(mesh->mTangents[i].z);
      vertex.Tangent = vector;
      vector.setX(mesh->mBitangents[i].x);
      vector.setY(mesh->mBitangents[i].y);
      vector.setZ(mesh->mBitangents[i].z);
      vertex.Bitangent = vector;
    } else {
      vertex.TexCoords = QVector2D(0.0f, 0.0f);
    }
    vertices.push_back(vertex);
  }
  for (uint i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (uint j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  if (mesh->mMaterialIndex >= 0) {
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuseMaps = loadMaterialTextures(
        material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    std::vector<Texture> specularMaps = loadMaterialTextures(
        material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    std::vector<Texture> normalMaps =
        loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    std::vector<Texture> heightMaps =
        loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
  }
  return Mash(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat,
                                                 aiTextureType type,
                                                 QString typeName) {
  std::vector<Texture> textures;
  for (uint i = 0; i < mat->GetTextureCount(type); i++) {
    aiString str;
    bool skip = false;
    mat->GetTexture(type, i, &str);
    for (uint j = 0; j < texture_loaded.size(); j++) {
      if (std::strcmp(texture_loaded[j].path.data(), str.C_Str()) == 0) {
        textures.push_back(texture_loaded[j]);
        skip = true;
        break;
      }
    }
    if (!skip) {
      Texture texture;
      texture.id = TextureFromFile(str.C_Str(), directory);
      texture.type = typeName;
      texture.path = str.C_Str();
      textures.push_back(texture);
      texture_loaded.push_back(texture);
    }
  }
  return textures;
}

GLuint Model::TextureFromFile(const char *name, const QString &directory,
                              bool gamma) {
  Q_UNUSED(gamma);
  QString file = QString(name);
  QString filename = directory + '/' + file;
  GLuint textureId;
  glGenTextures(1, &textureId);
  int width, height, nrComponents;
  uchar *data = stbi_load(filename.toStdString().c_str(), &width, &height,
                          &nrComponents, 0);
  if (data) {
    GLenum format = GL_RGBA;
    if (nrComponents == 1)
      format = GL_RED;
    else if (nrComponents == 3)
      format = GL_RGB;
    else if (nrComponents == 4)
      format = GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
  } else {
    stbi_image_free(data);
  }
  return textureId;
}
