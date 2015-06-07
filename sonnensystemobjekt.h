#ifndef SONNENSYSTEMOBJEKT_H
#define SONNENSYSTEMOBJEKT_H
#include<QOpenGLBuffer>
#include<QOpenGLShaderProgram>
#include<QOpenGLShader>
#include<QOpenGLTexture>
#include<vector>
#include "cam.h"
#include "modelloader.h"



class SonnensystemObjekt
{
public:
    SonnensystemObjekt();
    ~SonnensystemObjekt();

    QMatrix4x4 matrix;
    QMatrix4x4 invtransmatrix;
    std::vector<SonnensystemObjekt*>* children;
    QOpenGLShaderProgram* shaderProgram;
    float dist;
    float winkelParent;
    float winkelSpeedParent;
    float winkelSelf;
    float winkelSpeedSelf;
    float timer;
    bool isSun;
    bool usesNormals;

    GLfloat* vboData;
    GLuint* indexData;
    unsigned int vboLength;
    unsigned int iboLength;

    QOpenGLTexture* qTex;
    QOpenGLTexture* qTexWave;

    void buildSystem();
    void copyBuffer(SonnensystemObjekt*);
    void loadVertices();
    void loadModel(QString, bool);
    void loadTexture(QString);
    void setShaderProgram(QOpenGLShaderProgram* myshader);
    void render(QMatrix4x4, myCam*, int);



    QOpenGLBuffer* vbo;
    QOpenGLBuffer* ibo;
};
float myMod(float f, int i);
#endif // SONNENSYSTEMOBJEKT_H
