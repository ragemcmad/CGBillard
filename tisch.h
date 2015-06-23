#ifndef TISCH_H
#define TISCH_H
#include "gameobject.h"

class Tisch : public GameObject
{
    GLfloat waveIsActive[16];
    GLfloat waveStartPosX[16];
    GLfloat waveStartPosZ[16];
    GLfloat waveDuration[16];
    GLfloat waveTimeLeft[16];


    GLfloat* vboDataLow;
    GLuint* indexDataLow;


    unsigned int vboLengthLow;
    unsigned int iboLengthLow;

    QOpenGLBuffer* vboLow;
    QOpenGLBuffer* iboLow;


public:
    std::vector<QVector3D*>* kugelPositions;
    std::vector<bool*>* kugelActive;
    std::vector<QVector3D*>* kugelColor;

    Tisch();
    ~Tisch();
    void loadShader();
    void render(myCam* cam,int kugel);
    void generateWave(float xPosition,float zPosition,float duration);
    void loadModelLow(QString path);

};

#endif // TISCH_H
