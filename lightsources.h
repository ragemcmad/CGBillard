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
    std::vector<Animation>* animations[4];
    float moveDuration[4];
    float moveTime[4];
    QVector3D moveStart[4];
    QVector3D moveZiel[4];

    bool isMoving[4];

    void queueAnimation(QVector3D ziel, int pos, int duration = 500);
    void nextAnimation(int pos);
    void moveStep(float time);

    void adjustIntensity(int helligkeit);

    void render(myCam*);

};

#endif // LIGHTSOURCE_H
