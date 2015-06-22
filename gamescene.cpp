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
    this->kugelPositions = new std::vector<QVector3D*>();
    this->kugelActive = new std::vector<bool*>();
    this->kugelColor = new std::vector<QVector3D*>();
    this->kugelIndex = new std::vector<int>();
    this->KugelnAlle = new std::vector<Kugel*>();
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
    this->tischBoden->kugelPositions = this->kugelPositions;
    this->tischBoden->kugelActive = this->kugelActive;
    this->tischBoden->kugelColor = this->kugelColor;

    p = path::getPath();
    Kugel* kugelWhite = new Kugel(0);
    kugelWhite->loadModel(p.append(QString("models/sphere_high.obj")));
    kugelWhite->loadTexture(QString(":/textures/kugelWhite.png"));
    kugelWhite->loadShader();
    kugelWhite->loadLights(this->lights);
    kugelWhite->worldMatrix.translate(0,0,18);
    this->secondaryObjects->push_back(kugelWhite);
    this->KugelnAlle->push_back(kugelWhite);
    kugelWhite->setVector(this->secondaryObjects);
    kugelWhite->updatePosition();
    this->kugelPositions->push_back(kugelWhite->pos);
    this->kugelActive->push_back(&kugelWhite->isVisible);
    this->kugelColor->push_back(kugelWhite->color);
    this->kugelIndex->push_back(0);
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
            case 11:kugel->worldMatrix.translate(0,0,zpos); kugel->color = new QVector3D(255,127,0) ;break;
        case 1:kugel->worldMatrix.translate(-1*abstandx/2 ,0,zpos+1*abstandz); kugel->color = new QVector3D(255,255,0); break;
            case 3:kugel->worldMatrix.translate(1*abstandx/2,0,zpos+1*abstandz); kugel->color = new QVector3D(255,127,0); break;
            case 14:kugel->worldMatrix.translate(-1*abstandx,0,zpos+2*abstandz); kugel->color = new QVector3D(51,104,51); break;
            case 8: // schwarze Kugel
                //kugel->isVisible = false;
				kugel->worldMatrix.translate(0*abstandx,0,zpos+2*abstandz); 
                kugel->meineAktiven = NULL;
				kugel->meineEingelochten = NULL;
                kugel->color = new QVector3D(0,0,0);
				break;
            case 13:kugel->worldMatrix.translate(1*abstandx,0,zpos+2*abstandz); kugel->color = new QVector3D(255,183,112); break;
            case 7:kugel->worldMatrix.translate(-3*abstandx/2,0,zpos+3*abstandz); kugel->color = new QVector3D(159,7,7); break;
            case 15:kugel->worldMatrix.translate(-1*abstandx/2,0,zpos+3*abstandz); kugel->color = new QVector3D(159,7,7); break;
            case 9:kugel->worldMatrix.translate(+1*abstandx/2,0,zpos+3*abstandz); kugel->color = new QVector3D(255,255,0); break;
            case 2:kugel->worldMatrix.translate(3*abstandx/2,0,zpos+3*abstandz); kugel->color = new QVector3D(0,0,255); break;
            case 12:kugel->worldMatrix.translate(-2*abstandx,0,zpos+4*abstandz); kugel->color = new QVector3D(114,0,138); break;
            case 4:kugel->worldMatrix.translate(-1*abstandx,0,zpos+4*abstandz); kugel->color = new QVector3D(114,0,138); break;
            case 10:kugel->worldMatrix.translate(0*abstandx,0,zpos+4*abstandz); kugel->color = new QVector3D(0,0,255); break;
            case 6:kugel->worldMatrix.translate(1*abstandx,0,zpos+4*abstandz); kugel->color = new QVector3D(51,104,51); break;
            case 5:kugel->worldMatrix.translate(2*abstandx,0,zpos+4*abstandz); kugel->color = new QVector3D(255,183,112); break;
        }
        this->secondaryObjects->push_back(kugel);
        kugel->setVector(this->secondaryObjects);
        kugel->updatePosition();
        this->kugelPositions->push_back(kugel->pos);
        this->kugelActive->push_back(&kugel->isVisible);
        kugel->color->setX(kugel->color->x()/ 255.0);
        kugel->color->setY(kugel->color->y()/ 255.0);
        kugel->color->setZ(kugel->color->z()/ 255.0);
        this->kugelColor->push_back(kugel->color);
        this->kugelIndex->push_back(i);
        this->KugelnAlle->push_back(kugel);
    }

    this->lights->initLights();
    //this->lights->copyBuffer(kugelWhite);
    //this->lights->loadTexture(QString(":/textures/powerbar.png"));

    this->gui = new GUI();
    this->gui->loadShader();
    this->gui->setVector(this->secondaryObjects);
}

void GameScene::renderScene(myCam* cam, int kugel)
{
    myCam kugelCam(90.0f, 1.0f);


    if(kugel >= 0)
    {
        QMatrix4x4 position;
        position.setToIdentity();
        position.translate(-*this->KugelnAlle->at(kugel)->pos);
        kugelCam.viewMatrix = position;

        cam = &kugelCam;

        QVector3D campos = *this->KugelnAlle->at(kugel)->pos;
        QVector3D camdir[6] =
        {
            QVector3D(1,0,0),
            QVector3D(-1,0,0),
            QVector3D(0,1,0),
            QVector3D(0,-1,0),
            QVector3D(0,0,1),
            QVector3D(0,0,-1)
        };

        QVector3D camup[6] =
        {
            QVector3D(0,1,0),
            QVector3D(0,1,0),
            QVector3D(0,0,1),
            QVector3D(0,0,1),
            QVector3D(0,1,0),
            QVector3D(0,1,0)
        };

        for (int i = 0; i < 6; ++i)
        {
            QVector3D camtarget = campos + camdir[i];

            cam->viewMatrixCube[i].setToIdentity();
            cam->viewMatrixCube[i].lookAt(campos, camtarget,camup[i]);
        }
        cam->isCubeCamera = true;
    }

    if(kugel==-1)
    {
        this->lights->render(cam);
    }

    this->tischBoden->render(cam, kugel);
    for(uint i = 0; i< this->primaryObjects->size();i++)
    {
        this->primaryObjects->at(i)->render(cam,kugel);
    }

    this->secondaryObjects->at(0)->quickSort(0,15,this->KugelnAlle, *this->kugelIndex,cam->getPositionFromViewMatrix(cam->viewMatrix));

    for(int i = 15; i>= 0;i--)
    {
        this->secondaryObjects->at(this->kugelIndex->at(i))->render(cam,kugel);
    }



}

bool GameScene::hasMovingBalls(){
    for (int i=0; i<this->secondaryObjects->size();i++)
    {
        if(this->secondaryObjects->at(i)->isMoving())
            return true;
    }
    return false;
}

