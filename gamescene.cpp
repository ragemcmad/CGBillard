#include "gamescene.h"
#include "gameobject.h"
#include "path.h"
#include <vector>
#include <sstream>
#include <string>

GameScene::GameScene()
{
    this->primaryObjects = new std::vector<GameObject*>();
    this->secondaryObjects = new std::vector<Kugel*>();
	this->halbeKugeln = new std::vector<Kugel*>();
	this->ganzeKugeln = new std::vector<Kugel*>();
	this->eingelochteHalbe = new std::vector<Kugel*>();
	this->eingelochteGanze = new std::vector<Kugel*>();

}

GameScene::~GameScene()
{

}

void GameScene::initScene()
{
    this->lights = new LightSources();


    QString p = path::getPath();

    GameObject* koe = new GameObject();
    koe->loadModel(p.append(QString("models/koe.obj")));
    koe->loadTexture(QString(":/textures/koe.png"));
    koe->loadShader();
    koe->loadLights(this->lights);
    koe->worldMatrix.scale(0.5,0.5,0.5);
    this->primaryObjects->push_back(koe);

    p = path::getPath();
    GameObject* tisch = new GameObject();
    tisch->loadModel(p.append(QString("models/tisch.obj")));
    tisch->loadTexture(QString(":/textures/table.png"));
    tisch->loadShader();
    tisch->loadLights(this->lights);
    tisch->worldMatrix.scale(0.5,1,0.5);
    this->primaryObjects->push_back(tisch);   

    p = path::getPath();
    GameObject* tischbeine = new GameObject();
    tischbeine->loadModel(p.append(QString("models/stand.obj")));
    tischbeine->loadTexture(QString(":/textures/stand.png"));
    tischbeine->loadShader();
    tischbeine->loadLights(this->lights);
    tischbeine->worldMatrix.scale(0.5,1,0.5);
    this->primaryObjects->push_back(tischbeine);


    p = path::getPath();
    this->tischBoden = new Tisch();
    this->tischBoden->loadModel(p.append(QString("models/bodenHigh.obj")));
    this->tischBoden->loadTexture(QString(":/textures/plattehigh.png"));
    this->tischBoden->loadShader();
    this->tischBoden->loadLights(this->lights);
    this->tischBoden->worldMatrix.scale(0.5,1,0.5);


    p = path::getPath();
    Kugel* kugelWhite = new Kugel(0);
    kugelWhite->loadModel(p.append(QString("models/sphere_high.obj")));
    kugelWhite->loadTexture(QString(":/textures/kugelWhite.png"));
    kugelWhite->loadShader();
    kugelWhite->loadLights(this->lights);
    kugelWhite->worldMatrix.translate(10,0,0);
    this->secondaryObjects->push_back(kugelWhite);
    kugelWhite->setVector(this->secondaryObjects);
    kugelWhite->updatePosition();
    //kugelWhite->v->setZ(-0.9);
    //kugelWhite->v->setX(0.01);

    kugelWhite->meineAktiven = NULL;
    kugelWhite->meineEingelochten = NULL;

    float zpos = -18;
    float abstandz = -1.75;
    float abstandx = 2.01;
    for(int i = 1; i< 16;i++)
    {
        Kugel* kugel = new Kugel(i);
        kugel->copyBuffer(kugelWhite);
        std::stringstream convert;
        convert <<":/textures/kugel"<< i<<".png";
        kugel->loadTexture(QString::fromStdString(convert.str()));
        kugel->loadShader();
        kugel->loadLights(this->lights);
		if (i>8)
		{
			this->halbeKugeln->push_back(kugel);
			kugel->meineAktiven = this->halbeKugeln;
			kugel->meineEingelochten = this->eingelochteHalbe;
		}
		else if (i<8)
		{
			this->ganzeKugeln->push_back(kugel);
			kugel->meineAktiven = this->ganzeKugeln;
			kugel->meineEingelochten = this->eingelochteGanze;
		}
			
        switch(i)
        {
            case 11:kugel->worldMatrix.translate(0,0,zpos); break;
            case 1:kugel->worldMatrix.translate(-1*abstandx/2 ,0,zpos+1*abstandz); break;
            case 3:kugel->worldMatrix.translate(1*abstandx/2,0,zpos+1*abstandz); break;
            case 14:kugel->worldMatrix.translate(-1*abstandx,0,zpos+2*abstandz); break;
            case 8: // schwarze Kugel
				kugel->worldMatrix.translate(0*abstandx,0,zpos+2*abstandz); 
                kugel->meineAktiven = NULL;
				kugel->meineEingelochten = NULL;
				break;
            case 13:kugel->worldMatrix.translate(1*abstandx,0,zpos+2*abstandz); break;
            case 7:kugel->worldMatrix.translate(-3*abstandx/2,0,zpos+3*abstandz); break;
            case 15:kugel->worldMatrix.translate(-1*abstandx/2,0,zpos+3*abstandz); break;
            case 9:kugel->worldMatrix.translate(+1*abstandx/2,0,zpos+3*abstandz); break;
            case 2:kugel->worldMatrix.translate(3*abstandx/2,0,zpos+3*abstandz); break;
            case 12:kugel->worldMatrix.translate(-2*abstandx,0,zpos+4*abstandz); break;
            case 4:kugel->worldMatrix.translate(-1*abstandx,0,zpos+4*abstandz); break;
            case 10:kugel->worldMatrix.translate(0*abstandx,0,zpos+4*abstandz); break;
            case 6:kugel->worldMatrix.translate(1*abstandx,0,zpos+4*abstandz); break;
            case 5:kugel->worldMatrix.translate(2*abstandx,0,zpos+4*abstandz); break;
        }
        this->secondaryObjects->push_back(kugel);
        kugel->setVector(this->secondaryObjects);
        kugel->updatePosition();
    }

    this->lights->initLights();
    //this->lights->copyBuffer(kugelWhite);
    //this->lights->loadTexture(QString(":/textures/powerbar.png"));

    this->gui = new GUI();
    this->gui->loadShader();
    this->gui->setVector(this->secondaryObjects);
}

void GameScene::renderScene(myCam* cam)
{
    this->lights->render(cam);
    this->tischBoden->render(cam);
    for(int i = 0; i< this->primaryObjects->size();i++)
    {
        this->primaryObjects->at(i)->render(cam);
    }
    for(int i = 0; i< this->secondaryObjects->size();i++)
    {
        this->secondaryObjects->at(i)->render(cam);
    }
    this->gui->render();
}
bool GameScene::hasMovingBalls(){
    for (int i=0; i<this->secondaryObjects->size();i++)
    {
        if(this->secondaryObjects->at(i)->isMoving())
            return true;
    }
    return false;
}

