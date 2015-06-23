#include <GL/glew.h>
#include "game.h"

Game::Game()
{
    turn = false;
    finish = false;
    setBall = false;
    teamsAreSet = false;
    hatEingelocht = false;
    hatGegnerEingelocht = false;
    killMe = false;

    myScene = new GameScene();
    myScene->initScene();
	cam = new myCam();
    cam->aktivatePlaymode(QVector3D(this->myScene->secondaryObjects->at(0)->worldMatrix.column(3).x(),this->myScene->secondaryObjects->at(0)->worldMatrix.column(3).y(),this->myScene->secondaryObjects->at(0)->worldMatrix.column(3).z()));
    this->whiteBall = this->myScene->secondaryObjects->at(0);
    this->blackBall = this->myScene->secondaryObjects->at(8);
    this->koe = this->myScene->primaryObjects->at(0);
    this->watch = false;
    this->hatEingelocht=false;
    this->hatGegnerEingelocht=false;
    this->updateKoe(this->myScene->gui->powerBarScale.y());
    SoundSys::playIntro();
}

Game::~Game()
{
}

void Game::cancel()
{
	if (this->cam->isMoving)
	{
		this->cam->moveTime = this->cam->moveDuration;
        this->updateKoe(this->myScene->gui->powerBarScale.y());
		return;
	}
	if (this->finish)
        this->resetGame();
    this->myScene->lights->intensity[0] = QVector3D(50,50,50);//(70,0,0);
    this->myScene->lights->intensity[1] = QVector3D(50,50,50);//(0,70,0);
    this->myScene->lights->intensity[2] = QVector3D(50,50,50);//(0,0,70)
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
        this->myScene->gui->powerBar.isVisible = false;
        this->cam->queueAnimation(QVector3D(0,40,1),QVector3D(0,0,0),100);
    }
    if(this->setBall)
    {
        bool collide = false;
        for (int i=1; i<this->myScene->KugelnAlle->size();i++)
        {
            this->whiteBall->updatePosition();
            if (this->whiteBall->pos->distanceToPoint(*(this->myScene->KugelnAlle->at(i)->pos))<2)
            {
                collide = true;
                SoundSys::playClack();
                break;
            }
        }
        if (!collide){
            this->setBall = false;
            this->koe->isVisible = true;
            this->cam->aktivatePlaymode(*this->whiteBall->pos);
            this->updateKoe(this->myScene->gui->powerBarScale.y());
            this->myScene->gui->powerBar.isVisible = true;
            this->watch = false;
            for (int i=0;i<this->myScene->KugelnAlle->size();i++)
            {
                this->myScene->KugelnAlle->at(i)->resetFirstKollision();
            }
        }
    }
}

void Game::camMove(int x, int y)
{
    if (!this->setBall)
        this->cam->camMove(x,y);
}

void Game::camRotate(int x, int y)
{
    this->cam->camRotate(x,y);
    updateKoe(this->myScene->gui->powerBarScale.y());
}

void Game::ballMove(int x, int z)
{
    if (this->setBall)
    {
        QVector4D column = this->whiteBall->worldMatrix.column(3);
        column.setX(column.x()+x);
        column.setZ(column.z()+z);
        this->whiteBall->worldMatrix.setColumn(3,column);
        this->whiteBall->updatePosition();
        //this->whiteBall->updatePosition();
        //this->whiteBall->pos->setX(this->whiteBall->pos->x()+x);
        //this->whiteBall->pos->setZ(this->whiteBall->pos->z()+z);
    }
}

void Game::updateKoe(float dist)
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
    this->koe->worldMatrix.translate(0,0,-1-dist);
}

void Game::resetGame()
{	
    this->killMe = true;
}

void Game::prepareLogic()
{
    uint countGanzeEingelocht = this->myScene->eingelochteGanze->size();
    uint countHalbeEingelocht = this->myScene->eingelochteHalbe->size();
    this->moveStuff(1);

    //generate wave
    for(uint i = countGanzeEingelocht;i<this->myScene->eingelochteGanze->size();i++)
    {
        QVector3D pos = *this->myScene->eingelochteGanze->at(i)->pos;
        this->myScene->tischBoden->generateWave(pos.x()*2,pos.z()*2,80);
    }
    for(uint i = countHalbeEingelocht;i<this->myScene->eingelochteHalbe->size();i++)
    {
        QVector3D pos = *this->myScene->eingelochteHalbe->at(i)->pos;
        this->myScene->tischBoden->generateWave(pos.x()*2,pos.z()*2,80);
    }
    this->myScene->gui->powerStep();

    // test auf eingelocht
    bool ganzeEingelocht = (countGanzeEingelocht < this->myScene->eingelochteGanze->size());
    bool halbeEingelocht = (countHalbeEingelocht < this->myScene->eingelochteHalbe->size());
    if (!teamsAreSet && (ganzeEingelocht | halbeEingelocht))
    {
        teamsAreSet = true;
        if ((!turn & ganzeEingelocht) | (turn & halbeEingelocht))
            this->p1HasFull = true;
        else
            this->p1HasFull = false;

        this->myScene->gui->setTeam(false);
    }

    // setze Flags falls eingelocht
    if (!turn) // turn P1
    {
      if ((p1HasFull && ganzeEingelocht) | (!p1HasFull && halbeEingelocht))
      {
          this->hatEingelocht =true;
      }
      if ((p1HasFull && halbeEingelocht) | (!p1HasFull && ganzeEingelocht))
      {
          this->hatGegnerEingelocht =true;
      }
    }
    else // turn P2
    {
        if ((!p1HasFull && ganzeEingelocht) | (p1HasFull && halbeEingelocht))
        {
            this->hatEingelocht =true;
        }
        if ((!p1HasFull && halbeEingelocht) | (p1HasFull && ganzeEingelocht))
        {
            this->hatGegnerEingelocht =true;
        }
    }
}

void Game::moveStuff(float time)
{
    //move Kugeln
    for(uint i = 0; i<this->myScene->secondaryObjects->size();i++)
    {
        if (!this->setBall)
            this->myScene->secondaryObjects->at(i)->gameProgress(0);
    }
    // move lights
    this->myScene->lights->moveStep(time);

    //move cam
    if (this->cam->isMoving)
        this->cam->moveStep(time);

    //grow powerbar
    this->myScene->gui->powerStep();
}

void Game::renderStuff()
{
    for(int i = 0; i< 1;i++)
    {
        this->myScene->secondaryObjects->at(i)->initFBO(128, 128);
        glBindFramebuffer(GL_FRAMEBUFFER, this->myScene->secondaryObjects->at(i)->fbo);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->myScene->renderObjectPOV(cam,i);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDrawBuffer(GL_BACK);

    this->myScene->renderPlayerPOV(cam);

    this->myScene->gui->render(turn);
}


// Aufruf bei eingelochter Schwarzen Kugel
void Game::setWinner()
{
    if (!this->turn) //p1 turn
        if (!this->teamsAreSet)
            this->myScene->gui->p2Win();
        else if (this->p1HasFull)
            if (this->myScene->ganzeKugeln->empty())
                this->myScene->gui->p1Win();
            else
                this->myScene->gui->p2Win();
        else if (this->myScene->halbeKugeln->empty())
                this->myScene->gui->p1Win();
            else
                this->myScene->gui->p2Win();

    //p2 turn
    else if (!this->teamsAreSet)
        this->myScene->gui->p1Win();
    else if (!this->p1HasFull)
        if (this->myScene->ganzeKugeln->empty())
            this->myScene->gui->p2Win();
        else
            this->myScene->gui->p1Win();
    else if (this->myScene->halbeKugeln->empty())
        this->myScene->gui->p2Win();
    else
        this->myScene->gui->p1Win();
}

void Game::gameStep()
{

    this->renderStuff();
    this->prepareLogic();

    // Gamestate-Changes:
    // keine Änderungen bei Animation, Spielende oder Ballplatzierung

    if (this->finish | this->setBall)
        return;
    // test auf spielende
    else if (!this->blackBall->isVisible && this->watch && !this->myScene->hasMovingBalls()) {
        this->finish = true;
        SoundSys::playApplause();
        this->setWinner();
    }
    // test ob rundenende
    else if (this->watch && !this->myScene->hasMovingBalls())
    {
        bool hitFullsFirst = (this->whiteBall->hitFirst<8 && this->whiteBall->hitFirst>0);
        bool hitHalfsFirst = (this->whiteBall->hitFirst<16 && this->whiteBall->hitFirst>8);
        bool hitOwnFirst = ((this->teamsAreSet && ((this->p1HasFull & !this->turn)|(!this->p1HasFull & this->turn)) & hitFullsFirst) | (this->teamsAreSet & ((!this->p1HasFull & !this->turn)|(this->p1HasFull & this->turn)) & hitHalfsFirst));
        // test auf spielerwechsel
        if (!this->whiteBall->isVisible | this->hatGegnerEingelocht | !this->hatEingelocht | !hitOwnFirst)
        {
            if (!this->whiteBall->isVisible)
            {
                QVector4D column = this->whiteBall->worldMatrix.column(3);
                column.setX(0);
                column.setY(0);
                column.setZ(18);
                this->whiteBall->worldMatrix.setColumn(3,column);
                this->whiteBall->updatePosition();
                this->whiteBall->isVisible = true;
                this->setBall = true;
            }
            this->turn = !(this->turn);
            this->myScene->gui->powerBarPos.setX(-(this->myScene->gui->powerBarPos.x()));
        }

        //Rundenende
        this->hatEingelocht = false;
        this->hatGegnerEingelocht = false;

        if (!this->setBall)
        {
            this->myScene->gui->powerBar.isVisible = true;
            this->koe->isVisible = true;
            this->cam->aktivatePlaymode(*this->whiteBall->pos);
            this->updateKoe(this->myScene->gui->powerBarScale.y());
            this->watch = false;
            for (uint i=0;i<this->myScene->KugelnAlle->size();i++)
            {
                this->myScene->KugelnAlle->at(i)->resetFirstKollision();
            }
        }
    }
    else
        return;

}

void Game::animateLights() // DiscoMode ON
{

    int dur = 800;

    this->myScene->lights->intensity[0] = QVector3D(100,0,0);//(70,0,0);
    this->myScene->lights->intensity[1] = QVector3D(0,100,0);//(0,70,0);
    this->myScene->lights->intensity[2] = QVector3D(0,0,100);//(0,0,70)

    //for (uint i = 0; i<10; i++)
    uint i = 0;
        this->myScene->lights->queueAnimation(this->myScene->lights->positions[(i+1)%4],i%4,dur);
        this->myScene->lights->queueAnimation(this->myScene->lights->positions[(i+3)%4],(i+1)%4,dur);
        this->myScene->lights->queueAnimation(this->myScene->lights->positions[(i+2)%4],(i+3)%4,dur);
        this->myScene->lights->queueAnimation(this->myScene->lights->positions[i%4],(i+2)%4,dur);
    this->myScene->tischBoden->generateWave(40,80,80);
    this->myScene->tischBoden->generateWave(-40,-80,80);

}


