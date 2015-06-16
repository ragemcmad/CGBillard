#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include<QOpenGLShaderProgram>
#include<vector>
#include"modelloader.h"
#include"path.h"
#include<QOpenGLBuffer>
#include<QOpenGLShaderProgram>
#include"cam.h"

class LightSources
{
    void loadShader();
    void loadModel(QString ex_path);

    QOpenGLShaderProgram* shaderProgram;
    GLfloat* vboData;
    GLuint* indexData;

    unsigned int vboLength;
    unsigned int iboLength;

    QOpenGLBuffer* vbo;
    QOpenGLBuffer* ibo;


public:
    LightSources();
    void initLights();
    QVector3D positions[4];
    QVector3D intensity[4];


    void render(myCam*);

};

#endif // LIGHTSOURCE_H
