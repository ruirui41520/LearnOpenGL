//#include "openglwidget.h"
//#include <QDebug>
//#include <QFile>

//static GLuint VBO, VAO,EBO;

//float vertices[] = {
//    0.5f,  0.5f, 0.0f,  // top right
//    0.5f, -0.5f, 0.0f,  // bottom right
//    -0.5f, -0.5f, 0.0f,  // bottom left
//    -0.5f,  0.5f, 0.0f   // top left
//};
//unsigned int indices[] = {  // note that we start from 0!
//                            0, 1, 3,  // first Triangle
//                            1, 2, 3   // second Triangle
//                         };

//OpenglWidget::OpenglWidget(QWidget* parent):QOpenGLWidget(parent)
//{
//}

//OpenglWidget::~OpenglWidget()
//{
//    glDeleteVertexArrays(1,&VAO);
//    glDeleteBuffers(1,&VBO);
//    glDeleteBuffers(1,&EBO);
//}

//void OpenglWidget::initializeGL()
//{
//    this->initializeOpenGLFunctions();

//    bool success = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/triangle.vert");
//    if(!success){
//        qWarning()<<"shader program addShaderFromSourceFile vertex failed";
//        return;
//    }

//    success = shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/triangle.frag");
//    if(!success){
//        qWarning()<<"shader program addShaderFromSourceFile fragment failed";
//        return;
//    }

//    success = shaderProgram.link();
//    if(!success){
//        qWarning() <<"link failed";
//        return;
//    }


//    glGenVertexArrays(1,&VAO);
//    glGenBuffers(1,&VBO);
//    glGenBuffers(1,&EBO);

//    glBindVertexArray(VAO);

//    glBindBuffer(GL_ARRAY_BUFFER,VBO);
//    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

//    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(void*)0);
//    glEnableVertexAttribArray(0);

//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);

//}

//void OpenglWidget::resizeGL(int w, int h)
//{
//    glViewport(0,0,w,h);
//}

//void OpenglWidget::paintGL()
//{
//    glClearColor(0.2f,0.3f,0.3f,1.0f);
//    glClear(GL_COLOR_BUFFER_BIT);

//    shaderProgram.bind();
//    glBindVertexArray(VAO);
//    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
//    shaderProgram.release();


//}
