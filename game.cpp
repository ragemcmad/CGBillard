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
    this->updateKoe();
}

void Game::cancel()
{
	if (this->cam->isMoving)
	{
		this->cam->moveTime = this->cam->moveDuration;
		return;
	}
	if (this->finish)
        this->resetGame();
}

void Game::shoot()
{
	
    if(this->watch == false)
    {
        float angle = -this->cam->getCamAngle()+180;
        this->whiteBall->v->setX(sin(angle*(3.1415926/180)) * (2 * this->myScene->gui->powerLevel/this->myScene->gui->maxPower));
        this->whiteBall->v->setY(0);
        this->whiteBall->v->setZ(cos(angle*(3.1415926/180)) * (2 * this->myScene->gui->powerLevel/this->myScene->gui->maxPower));
        this->watch = true;
        this->cam->aktivateWatchmode();
        this->koe->isVisible = false;
        this->cam->queueAnimation(QVector3D(0,30,50),QVector3D(0,0,0),100);
    }
}

void Game::camMove(int x, int y)
{
    this->cam->camMove(x,y);
}

void Game::camRotate(int x, int y)
{
    this->cam->camRotate(x,y);
    updateKoe();
}

void Game::updateKoe()
{
    float angle = -this->cam->getCamAngle()+180;
    this->koe->worldMatrix.setToIdentity();
    QVector3D position;
    position.setX(this->whiteBall->pos->x());
    position.setY(this->whiteBall->pos->y());
    position.setZ(this->whiteBall->pos->z());
    this->koe->worldMatrix.translate(position);
    this->koe->worldMatrix.rotate(angle,0,1,0);
    this->koe->worldMatrix.rotate(10,1,0,0);
    this->koe->worldMatrix.translate(0,0,-1);
}

void Game::resetGame()
{	
	this->finish = false;
    this->teamAreSet = false;
	this->turn = false;
	this->watch = false;
    this->myScene->initScene();
	delete this->cam;
	this->cam = new myCam();
	this->cam->aktivatePlaymode(QVector3D(this->myScene->secondaryObjects->at(0)->worldMatrix.column(3).x(),this->myScene->secondaryObjects->at(0)->worldMatrix.column(3).y(),this->myScene->secondaryObjects->at(0)->worldMatrix.column(3).z()));
    this->koe->isVisible = true;
	this->updateKoe();
}

void Game::gameStep()
{
    int countGanzeEingelocht = this->myScene->eingelochteGanze->size();
    int countHalbeEingelocht = this->myScene->eingelochteHalbe->size();

    for(int i = 0; i<this->myScene->secondaryObjects->size();i++)
    {
        this->myScene->secondaryObjects->at(i)->gameProgress(0);
    }

    //generate wave
    for(int i = countGanzeEingelocht;i<this->myScene->eingelochteGanze->size();i++)
    {
        QVector3D pos = *this->myScene->eingelochteGanze->at(i)->pos;
        this->myScene->tischBoden->generateWave(pos.x()*2,pos.z()*2,80);
    }
    for(int i = countHalbeEingelocht;i<this->myScene->eingelochteHalbe->size();i++)
    {
        QVector3D pos = *this->myScene->eingelochteHalbe->at(i)->pos;
        this->myScene->tischBoden->generateWave(pos.x()*2,pos.z()*2,80);
    }

    this->myScene->gui->powerStep();

    this->myScene->renderScene(cam);


    if (this->cam->isMoving)
        this->cam->moveStep(1);
    else if (this->finish)
        return;
    // test auf spielende
    else if (!this->blackBall->isVisible && this->watch && !this->myScene->hasMovingBalls()) {
        this->finish = true;
        //if (!this->turn) //p1 turn
        //	if (!this->teamsAreSet)
		//		this->myScene->gui->p2Win();
		//	else if (this->p1HasFull)
		//		if (this->myScene->ganzeKugeln->isEmpty())
		//			this->myScene->gui->p1Win();
		//		else
		//			this->myScene->gui->p2Win();
		//	else if (this->myScene->halbeKugeln->isEmpty())
		//			this->myScene->gui->p1Win();
		//		else
		//			this->myScene->gui->p2Win();
	
		////p2 turn
		//else if (!this->teamsAreSet)
		//	this->myScene->gui->p1Win();
		//else if (!this->p1HasFull)
		//	if (this->myScene->ganzeKugeln->isEmpty())
		//		this->myScene->gui->p2Win();
		//	else
		//		this->myScene->gui->p1Win();
		//else if (this->myScene->halbeKugeln->isEmpty())
		//	this->myScene->gui->p2Win();
		//else
		//	this->myScene->gui->p1Win();
        
    }
  // test ob rundenende
    else if (this->watch && !this->myScene->hasMovingBalls())
    {
        //test auf rundenende
        if (!this->whiteBall->isVisible)
        {
            //this->setBall = true;
            // temporär
            this->whiteBall->pos->setX(0);
            this->whiteBall->pos->setY(0);
            this->whiteBall->pos->setZ(18);
            this->whiteBall->isVisible = true;
        }
        this->turn = !this->turn;
        this->watch = false;
        this->koe->isVisible = true;
        this->cam->aktivatePlaymode(*this->whiteBall->pos);
        this->updateKoe();
    }
	else
        this->myScene->gui->powerStep();
}

void Game::showOff() // DiscoMode ON
{
    //QVector3D altePos = this->cam.getPosition();
    //QVector3D pos1 = (altePos-this->whiteBall->pos);
		
    //QMatrix4x4 rotaMatrix;
	//rotaMatrix.setToIdentity();
	//rotaMatrix.rotate(90,0,1,0);
	//(pos1*rotaMatrix).transpose();
		
	//this->cam.queueAnimation(
	
	
	//this->myScene->lights[0] = 
	
}

