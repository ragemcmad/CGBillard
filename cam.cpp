

#include "cam.h"
#include <math.h>


myCam::myCam(){
    this->dist = 10;
    this->step = 10;
    this->xwinkel = 0;
    this->ywinkel = 0;
    this->updateView();
    //this->viewMatrix.lookAt(QVector3D(0,0,-40), QVector3D(0,0,0), QVector3D(0,1,40));
    this->projMatrix.setToIdentity();
    this->projMatrix.perspective(95.0f, 1.0f, 0.1f, 1000.0f);
}


void myCam::camRotate(int x,int y)
{
    QMatrix4x4 rot1;
    rot1.setToIdentity();
    rot1.rotate(y*0.1,1,0,0);
    QMatrix4x4 rot2;
    rot2.setToIdentity();
    rot2.rotate(x*0.1,0,1,0);

    this->viewMatrix = rot1*rot2 * this->viewMatrix;
}

void myCam::camMove(int x, int y)
{
    QMatrix4x4 move;
    move.setToIdentity();
    move.translate(x,0,y);
    this->viewMatrix = move * this->viewMatrix;
}

void myCam::camDown(){
    this->xwinkel= (this->xwinkel+(360-this->step))%360;
    updateView();
}
void myCam::camUp(){
    this->xwinkel= (this->xwinkel+this->step)%360;
    updateView();
}
void myCam::camLeft(){
    this->ywinkel= (this->xwinkel+(360-this->step))%360;
    updateView();
}
void myCam::camRight(){
    this->ywinkel= (this->xwinkel+this->step)%360;
    updateView();
}

void myCam::zoomIn(){
    this->dist -= ((float)this->step)/10;
    if (this->dist < this->minDist)
        this->dist = this->minDist;
    updateView();
}
void myCam::zoomOut() {
    this->dist += (float)(this->step)/10;
    updateView();
}

void myCam::updateView(){
    x = (float)sin(this->ywinkel*(3.1415926/180))*this->dist;
    y = 0;
    z = (float)cos(this->ywinkel*(3.1415926/180))*this->dist;
    //this->viewMatrix.setToIdentity();
    this->viewMatrix.lookAt(QVector3D(x,y,z),QVector3D(0,0,0),QVector3D(0,1,0));
}

void myCam::moveUp(){
    y+=1;
    this->viewMatrix.setToIdentity();
    this->viewMatrix.lookAt(QVector3D(x,y,z),QVector3D(0,0,0),QVector3D(0,1,0));
}

void myCam::moveDown(){
    y-=1;
    this->viewMatrix.setToIdentity();
    this->viewMatrix.lookAt(QVector3D(x,y,z),QVector3D(0,0,0),QVector3D(0,1,0));
}
void myCam::moveLeft(){
    x-=1;
    this->viewMatrix.setToIdentity();
    this->viewMatrix.lookAt(QVector3D(x,y,z),QVector3D(0,0,0),QVector3D(0,1,0));
}
void myCam::moveRight(){
    x+=1;
    this->viewMatrix.setToIdentity();
    this->viewMatrix.lookAt(QVector3D(x,y,z),QVector3D(0,0,0),QVector3D(0,1,0));
}
void myCam::moveFront(){
    z+=1;
    this->viewMatrix.setToIdentity();
    this->viewMatrix.lookAt(QVector3D(x,y,z),QVector3D(0,0,0),QVector3D(0,1,0));
}
void myCam::moveBack(){
    z-=1;
    this->viewMatrix.setToIdentity();
    this->viewMatrix.lookAt(QVector3D(x,y+40,z),QVector3D(0,0,0),QVector3D(0,1,0));
}

void myCam::resetView(){
    this->ywinkel = 0;
    this->xwinkel = 0;
    this->updateView();
}

