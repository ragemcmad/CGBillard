#ifndef GAMESCENE_H
#define GAMESCENE_H

#include<vector>
#include "cam.h"
#include "kugel.h"
#include "tisch.h"
#include "koe.h"

class GameScene
{
public:
    GameScene();
    ~GameScene();

    std::vector<GameObject*>* primaryObjects;
    std::vector<Kugel*>* secondaryObjects;
    void initScene();
    void renderScene(myCam* cam);
    bool hasActives();

};

#endif // GAMESCENE_H
