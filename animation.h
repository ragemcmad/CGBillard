#ifndef ANIMATION_H
#define ANIMATION_H


#include<QOpenGLBuffer>
#include<QOpenGLShaderProgram>

class Animation
{
public:

    QVector3D moveZiel;
    QVector3D moveLookatZiel;
    float moveDuration;

    QVector3D moveStart;
    QVector3D moveLookatStart;

    Animation(QVector3D ziel, QVector3D zielLookAt, int duration);
};

#endif // ANIMATION_H
