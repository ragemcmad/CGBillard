#ifndef TISCH_H
#define TISCH_H
#include "gameobject.h"

class Tisch : public GameObject
{
public:
    Tisch();
    ~Tisch();
    void loadShader();
    void render(myCam* cam);
};

#endif // TISCH_H
