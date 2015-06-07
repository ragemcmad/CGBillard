#ifndef GAMESCENE_H
#define GAMESCENE_H

#include<vector>
#include "cam.h"
#include "kugel.h"
#include "tisch.h"

class GameScene
{
public:
    GameScene();
    ~GameScene();

    std::vector<Tisch*>* primaryObjects;
    std::vector<Kugel*>* secondaryObjects;

    void initScene();
    void renderScene(myCam* cam);

};

#endif // GAMESCENE_H
