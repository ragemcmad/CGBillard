#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include<QOpenGLShaderProgram>
#include<vector>
#include"gameobject.h"

class LightSources //: public GameObject
{
public:
    LightSource();
    void initLights();
    QVector3D positions[4];
    GLfloat intensity[4];

};

#endif // LIGHTSOURCE_H
