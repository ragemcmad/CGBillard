#include "game.h"

Game::Game(){
    myScene = new GameScene();
    myScene->initScene();
	cam = new myCam();
    cam->aktivatePlaymode(QVector3D(this->myScene->secondaryObjects->at(0)->worldMatrix.column(3).x(),this->myScene->secondaryObjects->at(0)->worldMatrix.column(3).y(),this->myScene->secondaryObjects->at(0)->worldMatrix.column(3).z()));
    this->whiteBall = this->myScene->secondaryObjects->at(0);
    this->blackBall = this->myScene->secondaryObjects->at(8);
    this->koe = this->myScene->primaryObjects->at(0);
    this->watch = false;
}

void Game::shoot()
{
    if(this->watch == false)
    {
        float angle = -this->cam->getCamAngle()+180;
        this->whiteBall->v->setX(sin(angle*(3.1415926/180)));
        this->whiteBall->v->setY(0);
        this->whiteBall->v->setZ(cos(angle*(3.1415926/180)));
        this->watch = true;
        this->cam->aktivateWatchmode();
        this->koe->isVisible = false;
    }
}

void Game::camMove(int x, int y)
{
    this->camMove(x,y);

}
void Game::camRotate(int x, int y)
{
    this->cam->camRotate(x,y);
    if(this->watch == false)
    {
        this->koe->isVisible = true;
        float angle = -this->cam->getCamAngle()+180;
        this->koe->worldMatrix.setToIdentity();
        this->koe->worldMatrix.rotate(10,1,0,0);
        this->koe->worldMatrix.rotate(angle,0,1,0);
        QVector3D position;
        position.setX(this->whiteBall->pos->x());
        position.setY(this->whiteBall->pos->y());
        position.setZ(this->whiteBall->pos->z());
        this->koe->worldMatrix.translate(position);
    }
}

void Game::gameStep(){
	
    this->myScene->renderScene(cam);
	
//	if (this->cam->isMoving)
//		this->cam->moveStep();
//	else if (this->finish)
//		;
//	// test auf spielende
//	else if (!this->blackBall.isActive && this->watch && !this->myScene.hasActives()) {
//		this->finish = true;
//		if (!this->turn) //p1 turn
//			if
//		else			 //p2 turn
//	}
// else if (!this->whiteBall.isActive && this->watch && !this->myScene.hasActives()) {
//		if (this->turn)
// 			this->turn = false;
//		else
//			this->turn = true;
//
//		//this->setBall = true;	
// 		this->whiteBall->v->setX(sin(angle*(3.1415926/180)));
//      this->whiteBall->v->setY(0);
//      this->whiteBall->v->setZ(cos(angle*(3.1415926/180)));
//  }
}
//void Game::turn(int player, bool &finish, bool &win)
//{
//
//}
