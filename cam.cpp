#include "cam.h"
#include <math.h>


myCam::myCam(){
    this->projMatrix.setToIdentity();
    this->projMatrix.perspective(95.0f, 1.0f, 0.1f, 1000.0f);
    this->viewMatrix.setToIdentity();
    this->viewMatrix.lookAt(QVector3D(0,50,30),QVector3D(0,0,0),QVector3D(0,1,0));
    this->activePlaymode = true;
    this->freeCameramode = false;
    this->angleX = 0;
    this->angleY = 0;
    this->distanz = 30;
    this->isMoving = false;
}

void myCam::moveStep()
{

}

void myCam::aktivatePlaymode(QVector3D kugelWhite)
{
    this->activePlaymode = true;
    this->kugelWhite = kugelWhite;
    int abstand = 30;
    QVector3D position;
    position.setX(kugelWhite.x());
    position.setY(kugelWhite.y());
    position.setZ(kugelWhite.z());
    if(position.x()==0 && position.y()==0 && position.z() == 0)
    {
        position.setZ(-1);
    }
    position.normalize();
    position.setX(position.x()*abstand + kugelWhite.x());
    position.setY(10);
    position.setZ(position.z()*abstand + kugelWhite.z());
    this->viewMatrix.setToIdentity();
    this->viewMatrix.lookAt(position,kugelWhite,QVector3D(0,1,0));
    this->freeCameramode = false;
}

void myCam::aktivateWatchmode()
{
    this->activePlaymode = false;
    this->freeCameramode = true;
}

float myCam::getCamAngle()
{
    return this->angleY;
}

void myCam::camRotate(int x,int y)
{
    if(this->freeCameramode)
    {
        QMatrix4x4 rot1;
        rot1.setToIdentity();
        rot1.rotate(y*0.1,1,0,0);
        QMatrix4x4 rot2;
        rot2.setToIdentity();
        rot2.rotate(x*0.1,0,1,0);

        this->viewMatrix = rot1*rot2 * this->viewMatrix;
    }
    else
    {
        this->angleX -= y*0.1;
        this->angleY += x*0.1;

        if(this->angleX > 60)
        {
            this->angleX = 60;
        }
        if(this->angleX<15)
        {
            this->angleX = 15;
        }

        this->viewMatrix.setToIdentity();
        this->viewMatrix.translate(0,0,-distanz);
        this->viewMatrix.rotate(angleX,1,0,0);
        this->viewMatrix.rotate(angleY,0,1,0);


        this->viewMatrix.translate(-kugelWhite);
    }
}

void myCam::camMove(int x, int y)
{
    if(this->freeCameramode == true)
    {
        QMatrix4x4 move;
        move.setToIdentity();
        move.translate(x,0,y);
        this->viewMatrix = move * this->viewMatrix;

    }


}

