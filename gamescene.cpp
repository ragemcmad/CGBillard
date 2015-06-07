#include "gamescene.h"
#include "gameobject.h"
#include <vector>

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
    Tisch* tisch = new Tisch();
    tisch->loadModel(QString("C:/Users/thoma_000/Documents/QT/qtp2/models/bodenHigh.obj"));
    tisch->loadTexture(QString(":/textures/plattehigh.png"));
    tisch->loadShader();
    tisch->worldMatrix.scale(0.5,1,0.5);

    Kugel* kugel1 = new Kugel(0);
    kugel1->loadModel(QString("C:/Users/thoma_000/Documents/QT/qtp2/models/sphere_high.obj"));

    for(int i = 0; i< 21;i++)
    {
        Kugel* kugel = new Kugel(i);
        kugel->copyBuffer(kugel1);
        kugel->loadTexture(QString(":/textures/earthmap1k.jpg"));
        kugel->loadShader();
        kugel->worldMatrix.translate(sin(i*0.6)*10,0,cos(i*0.6)*10);
        kugel->v->setX(-sinf(i*0.6)*0.1*i/7.0);
        kugel->v->setY(0);
        kugel->v->setZ(-cosf(i*0.6)*0.1);
        this->secondaryObjects->push_back(kugel);
        kugel->setVector(this->secondaryObjects);
        kugel->updatePosition();
    }
    this->primaryObjects->push_back(tisch);
    delete kugel1;
}

void GameScene::renderScene(myCam* cam)
{
    for(int i = 0; i< this->primaryObjects->size();i++)
    {
        this->primaryObjects->at(i)->render(cam);
    }
    for(int i = 0; i< this->secondaryObjects->size();i++)
    {
        this->secondaryObjects->at(i)->gameProgress(1);
        this->secondaryObjects->at(i)->render(cam);
    }
}


