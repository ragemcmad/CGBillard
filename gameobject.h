#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include<QOpenGLBuffer>
#include<QOpenGLShaderProgram>
#include<QOpenGLTexture>
#include"modelloader.h"
#include"cam.h"
#include"lightsources.h"

class GameObject
{
public:


    GameObject();
    ~GameObject();
    QMatrix4x4 worldMatrix;
    QOpenGLShaderProgram* shaderProgram;
    LightSources* lights;

    bool isVisible;

    GLfloat* vboData;
    GLuint* indexData;

    QOpenGLTexture* qTex;

    unsigned int vboLength;
    unsigned int iboLength;

    QOpenGLBuffer* vbo;
    QOpenGLBuffer* ibo;

    void render(myCam*,int kugel);
    void copyBuffer(GameObject* sso);
    void loadModel(QString path);
    void loadTexture(QString path);
    void loadShader();
    void loadLights(LightSources* lights);

};

#endif // GAMEOBJECT_H
