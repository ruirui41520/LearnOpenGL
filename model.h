#pragma once
#include "mash.h"
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <QImage>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QScopedPointer>
#include <QThread>
#include <QOpenGLFunctions>
#include "shader.h"

class Model
{
public:
    Model(QString path);
    void draw(Shader *shader);

protected:
    QVector<Mash> m_meshes;
    QString directory;
    std::vector<Texture> texture_loaded;
    void loadModel(QString path);
    void processNode(aiNode *node,const aiScene *scene);
    Mash processMash(aiMesh *mesh,const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat,aiTextureType type,QString typeName);
    GLuint TextureFromFile(const char *path, const QString &directory, bool gamma=false);
};
