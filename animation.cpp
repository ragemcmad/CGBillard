#include "animation.h"

Animation::Animation(QVector3D ziel,QVector3D zielLookAt,int duration)
{
    this->moveZiel = ziel;
    this->moveLookatZiel = zielLookAt;
    this->moveDuration = duration;
}

