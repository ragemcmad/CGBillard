#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include<QOpenGLShaderProgram>
#include<vector>

class LightSources
{
public:
    LightSource();
    void initLights();
    QVector3D positions[4];
    GLfloat intensity[4];

};

#endif // LIGHTSOURCE_H
