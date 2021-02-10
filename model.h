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

class Model
{
public:
    Model(QString path, QOpenGLFunctions_3_3_Core* glFunctions);
    void draw(QOpenGLShaderProgram *shader);

private:
    QVector<Mash> m_meshes;
    QString directory;
    QVector<Texture> texture_loaded;
    QOpenGLFunctions_3_3_Core* m_functions;
    void loadModel(QString path);
    void processNode(aiNode *node,const aiScene *scene);
    Mash processMash(aiMesh *mesh,const aiScene *scene);
    QVector<Texture> loadMaterialTextures(aiMaterial *mat,aiTextureType type,QString typeName);
    GLuint TextureFromFile(const char *path, const QString &directory, bool gamma=false);

};
