#ifndef GUI_H
#define GUI_H
#include "gameobject.h"
#include<QOpenGLBuffer>
#include<QOpenGLShaderProgram>
#include<QOpenGLTexture>
#include <vector>
#include"kugel.h"
#include"modelloader.h"
#include"guitexture.h"
#include"path.h"
#include <sstream>

class GUI
{

public:
    GUI();
    GuiTexture kugeln[14];
    GuiTexture players;
    std::vector<Kugel*>* kugelnVector;
    bool p1Full;

    void render();
    void loadShader();
    void setTeam(bool p1Full);
    void setVector(std::vector<Kugel*>* vec);

};

#endif // GUI_H
