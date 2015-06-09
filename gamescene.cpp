#include "gamescene.h"
#include "gameobject.h"
#include "path.h"
#include <vector>
#include <sstream>
#include <string>

GameScene::GameScene()
{
    this->primaryObjects = new std::vector<Tisch*>();
    this->secondaryObjects = new std::vector<Kugel*>();

}

GameScene::~GameScene()
{

}

void GameScene::initScene()
{
    QString p = path::getPath();

    Tisch* tisch = new Tisch();
    tisch->loadModel(p.append(QString("models/tisch.obj")));
    tisch->loadTexture(QString(":/textures/table.png"));
    tisch->loadShader();
    tisch->worldMatrix.scale(0.5,1,0.5);
    this->primaryObjects->push_back(tisch);

    p = path::getPath();
    Tisch* tischbodenH = new Tisch();
    tischbodenH->loadModel(p.append(QString("models/bodenHigh.obj")));
    tischbodenH->loadTexture(QString(":/textures/plattehigh.png"));
    tischbodenH->loadShader();
    tischbodenH->worldMatrix.scale(0.5,1,0.5);
    this->primaryObjects->push_back(tischbodenH);

    p = path::getPath();
    Tisch* tischbodenL = new Tisch();
    tischbodenL->loadModel(p.append(QString("models/bodenLow.obj")));
    tischbodenL->loadTexture(QString(":/textures/plattelow.png"));
    tischbodenL->loadShader();
    tischbodenL->worldMatrix.scale(0.5,1,0.5);
    //this->primaryObjects->push_back(tischbodenL);

    p = path::getPath();
    Kugel* kugelWhite = new Kugel(0);
    kugelWhite->loadModel(p.append(QString("models/sphere_high.obj")));
    kugelWhite->loadTexture(QString(":/textures/kugelWhite.png"));
    kugelWhite->loadShader();
    kugelWhite->worldMatrix.translate(0,0,18);
    this->secondaryObjects->push_back(kugelWhite);
    kugelWhite->setVector(this->secondaryObjects);
    kugelWhite->updatePosition();
    kugelWhite->v->setZ(-0.9);
    kugelWhite->v->setX(0.01);


    float zpos = -18;
    float abstandz = -2;//-1.75;
    float abstandx = 2.5;//2.01;
    for(int i = 1; i< 16;i++)
    {
        Kugel* kugel = new Kugel(i);
        kugel->copyBuffer(kugelWhite);
        std::stringstream convert;
        convert <<":/textures/kugel"<< i<<".png";
        kugel->loadTexture(QString::fromStdString(convert.str()));
        kugel->loadShader();
        switch(i)
        {
            case 11:kugel->worldMatrix.translate(0,0,zpos); break;
            case 1:kugel->worldMatrix.translate(-1*abstandx/2 ,0,zpos+1*abstandz); break;
            case 3:kugel->worldMatrix.translate(1*abstandx/2,0,zpos+1*abstandz); break;
            case 14:kugel->worldMatrix.translate(-1*abstandx,0,zpos+2*abstandz); break;
            case 8:kugel->worldMatrix.translate(0*abstandx,0,zpos+2*abstandz); break;
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

}

void GameScene::renderScene(myCam* cam)
{
    for(int i = 0; i< this->primaryObjects->size();i++)
    {
        this->primaryObjects->at(i)->render(cam);
    }
    for(int i = 0; i< this->secondaryObjects->size();i++)
    {
        if(this->secondaryObjects->at(i)->gameProgress(1))
        {
            //Kugel wurde eingelocht
            this->secondaryObjects->at(i)->eingelocht = true;
        }
        if(!this->secondaryObjects->at(i)->eingelocht)
        {
            this->secondaryObjects->at(i)->render(cam);
        }
    }
}

