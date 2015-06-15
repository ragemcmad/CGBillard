#include "lightsources.h"

LightSources::LightSource()
{

}
void LightSources::initLights()
{
    this->positions[0] = QVector3D(-200,500,-300);
    this->positions[1] = QVector3D(+200,500,-300);
    this->positions[2] = QVector3D(+200,500,+300);
    this->positions[3] = QVector3D(-200,500,+300);
    this->intensity[0] = 0.3;
    this->intensity[1] = 0.3;
    this->intensity[2] = 0.3;
    this->intensity[3] = 0.3;
}

