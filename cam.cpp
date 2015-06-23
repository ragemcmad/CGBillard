#include "cam.h"
#include <math.h>


myCam::myCam(float fov, float aspect){
    this->projMatrix.setToIdentity();
    this->projMatrix.perspective(fov, aspect, 0.01f, 1000.0f);
    this->viewMatrix.setToIdentity();
    this->viewMatrix.lookAt(QVector3D(0,50,30),QVector3D(0,0,0),QVector3D(0,1,0));
    this->activePlaymode = true;
    this->freeCameramode = false;
    this->angleX = 0;
    this->angleY = 0;
    this->distanz = 30;
    this->isMoving = false;
    this->animations = std::vector<Animation>();
    this->isCubeCamera = false;
}

void myCam::queueAnimation(QVector3D ziel, QVector3D zielLookat, int duration)
{
    Animation aniNew = Animation(ziel,zielLookat,duration);
    this->animations.push_back(aniNew);
	if (!this->isMoving)
		this->nextAnimation();
		
}

QVector3D myCam::getPositionFromViewMatrix(QMatrix4x4 matrix)
{
    QMatrix4x4 viewRot = matrix;
    viewRot.setColumn(3, QVector4D(0,0,0,1));
    QVector4D p = -(viewRot.transposed() * matrix.column(3));
    return QVector3D(p.x(), p.y(), p.z());
}

void myCam::moveStep(int time)
{	
    if(this->isMoving)
    {
        this->moveTime += time;
        if (this->moveTime >= this->moveDuration)
        {
            this->viewMatrix.setToIdentity();
            this->viewMatrix.lookAt(this->moveZiel,this->moveLookatZiel,QVector3D(0,1,0));
            this->isMoving = false;
			
            if (!this->animations.empty())
				this->nextAnimation();
        }
        else
        {
            //QVector3D iamAt = (this->moveZiel-this->moveStart) * sin((this->moveTime/this->moveDuration)*3.1415926/2.0)+this->moveStart;
            QVector3D iamAt = (this->moveZiel-this->moveStart) * (-1.0/2.0*cos((this->moveTime/this->moveDuration)*3.1415926)+0.5)+this->moveStart;
            QVector3D ilookAt = (this->moveLookatZiel-this->moveLookatStart) * (-1.0/2.0*cos((this->moveTime/this->moveDuration)*3.1415926)+0.5)+this->moveLookatStart;
            this->viewMatrix.setToIdentity();
            this->viewMatrix.lookAt(iamAt, ilookAt, QVector3D(0,1,0));
        }
    }
}

void myCam::nextAnimation()
{
    if (!this->animations.empty())
	{
		this->isMoving = true;
		Animation ani = this->animations.at(this->animations.size()-1);
		this->animations.pop_back();
		
		this->moveZiel = ani.moveZiel;
		this->moveStart = getPositionFromViewMatrix(this->viewMatrix);
		this->moveLookatZiel = ani.moveLookatZiel;
		this->moveTime = 0;
		this->moveDuration = ani.moveDuration;
		float dist = (ani.moveZiel.distanceToPoint(ani.moveLookatZiel));
		QMatrix4x4 matrixcopy;
		matrixcopy.translate(0,0,dist);
		matrixcopy = matrixcopy * this->viewMatrix;
		this->moveLookatStart = this->getPositionFromViewMatrix(matrixcopy);
	}
}

void myCam::aktivatePlaymode(QVector3D kugelWhite, int abstand)
{
    this->activePlaymode = true;
    this->kugelWhite = kugelWhite;

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
    position.setY(8);
    position.setZ(position.z()*abstand + kugelWhite.z());
    //this->viewMatrix.setToIdentity();
    //this->viewMatrix.lookAt(position,kugelWhite,QVector3D(0,1,0));
    this->queueAnimation(position,kugelWhite,100);
    position = position-kugelWhite;

    if(position.x()>0 && position.z()>0)
    {
        this->angleY = atan(position.z()/position.x())*180/3.1415926-90;
    }
    else if(position.x()<0 && position.z()>0)
    {
        this->angleY = atan(-position.x()/position.z())*180/3.1415926;
    }
    else if(position.x()<0 && position.z()<0)
    {
        this->angleY = atan(position.z()/position.x())*180/3.1415926+90;
    }
    else if(position.x()>0 && position.z()<0)
    {
        this->angleY = atan(position.x()/-position.z())*180/3.1415926+180;
    }
    else if(position.x() == 0)
    {
        if(position.z()>0)
            this->angleY = 0;
        else
            this->angleY = 180;
    }
    else if(position.z() == 0)
    {
        if(position.x()>0)
            this->angleY = 270;
        else
            this->angleY = 90;
    }
    this->angleX = 15;
    this->camRotate(0,0);
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

