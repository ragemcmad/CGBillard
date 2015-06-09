#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include<QOpenGLBuffer>
#include<QOpenGLShaderProgram>
#include<QOpenGLTexture>
#include"modelloader.h"
#include"cam.h"

class GameObject
{
public:


    GameObject();
    ~GameObject();
    QMatrix4x4 worldMatrix;
    QOpenGLShaderProgram* shaderProgram;

    bool isVisible = true;

    GLfloat* vboData;
    GLuint* indexData;

    QOpenGLTexture* qTex;

    unsigned int vboLength;
    unsigned int iboLength;

    QOpenGLBuffer* vbo;
    QOpenGLBuffer* ibo;

    void render(myCam*);
    void copyBuffer(GameObject* sso);
    void loadModel(QString path);
    void loadTexture(QString path);
    void loadShader();

};

#endif // GAMEOBJECT_H
