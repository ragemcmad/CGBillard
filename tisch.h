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


public:
    std::vector<QVector3D*>* kugelPositions;
    Tisch();
    ~Tisch();
    void loadShader();
    void render(myCam* cam);
    void generateWave(float xPosition,float zPosition,float duration);

};

#endif // TISCH_H
