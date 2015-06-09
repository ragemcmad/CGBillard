#include "cam.h"
#include <math.h>


myCam::myCam(){
    this->projMatrix.setToIdentity();
    this->projMatrix.perspective(95.0f, 1.0f, 0.1f, 1000.0f);
    this->viewMatrix.setToIdentity();
    this->viewMatrix.lookAt(QVector3D(0,50,30),QVector3D(0,0,0),QVector3D(0,1,0));
    this->activePlaymode = true;
    this->freeCameramode = false;
}

void myCam::aktivatePlaymode(QVector3D kugelWhite)
{
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
        QMatrix4x4 rotation;
        rotation.setToIdentity();
        rotation.rotate(y*0.5,1,0,0);
        rotation.rotate(x*0.5,0,1,0);

        this->viewMatrix.translate(this->kugelWhite);
        viewMatrix = viewMatrix * rotation;
        this->viewMatrix.translate(-this->kugelWhite);


        //QVector3D position;
        //position.setX(this->viewMatrix.row(0).x());
        //position.setY(this->viewMatrix.row(0).y());
        //position.setZ(this->viewMatrix.row(0).z());
        //this->viewMatrix.setToIdentity();
        //this->viewMatrix.lookAt(position,this->kugelWhite,QVector3D(0,100,0));


   //     QVector3D position;
   //     position.setX(this->viewMatrix.column(3).x()-this->kugelWhite.x());
   //     position.setY(this->viewMatrix.column(3).y()-this->kugelWhite.y());
   //     position.setZ(this->viewMatrix.column(3).z()-this->kugelWhite.z());
   //
   //     QMatrix4x4 rotation;
   //     rotation.setToIdentity();
   //     rotation.rotate(y*0.5,1,0,0);
   //     rotation.rotate(x*0.5,0,1,0);
   //     position = rotation * position;
   //
   //     position.setX(position.x()+this->kugelWhite.x());
   //     position.setY(position.y()+this->kugelWhite.y());
   //     position.setZ(position.z()+this->kugelWhite.z());
   //
   //     this->viewMatrix.setToIdentity();
   //     this->viewMatrix.lookAt(position,this->kugelWhite,QVector3D(0,1,0));
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

