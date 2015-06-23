#ifndef GAMESCENE_H
#define GAMESCENE_H

#include<vector>
#include "cam.h"
#include "kugel.h"
#include "tisch.h"
#include "koe.h"
#include "gui.h"
#include "lightsources.h"

class GameScene
{
public:
    GameScene();
    ~GameScene();

    Tisch *tischBoden;
    std::vector<GameObject*>* primaryObjects;
    std::vector<Kugel*>* secondaryObjects;
	
    std::vector<Kugel*>* halbeKugeln;
    std::vector<Kugel*>* eingelochteHalbe;
    std::vector<Kugel*>* ganzeKugeln;
    std::vector<Kugel*>* eingelochteGanze;
    std::vector<Kugel*>* KugelnAlle;

    std::vector<QVector3D*>* kugelPositions;
    std::vector<bool*>* kugelActive;
    std::vector<QVector3D*>* kugelColor;
    std::vector<int>* kugelIndex;
    GUI *gui;

    void initScene();
    void resetScene();
    void initTraining1();
    void initShow();
    void render(myCam* cam, int kugel = -1);
    void renderPlayerPOV(myCam* cam);
    void renderObjectPOV(myCam* cam, int id);
    bool hasMovingBalls();

    LightSources* lights;

};

#endif // GAMESCENE_H
