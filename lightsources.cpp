#include "lightsources.h"

LightSources::LightSource()
{

}
void LightSources::initLights()
{
    this->positions[0] = QVector3D(-20,50,-30);
    this->positions[1] = QVector3D(+20,50,-30);
    this->positions[2] = QVector3D(+20,50,+30);
    this->positions[3] = QVector3D(-20,50,+30);
    this->intensity[0] = 30;
    this->intensity[1] = 30;
    this->intensity[2] = 30;
    this->intensity[3] = 30;
}

