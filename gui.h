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
    ~GUI();
    GuiTexture kugeln[14];
    GuiTexture players1;
    GuiTexture players2;
	GuiTexture winSign;
	GuiTexture powerBar;
    std::vector<Kugel*>* kugelnVector;
    bool p1Full;
	float powerLevel;
    float maxPower;
    float powerChange;
    float effectivePower;
	
    QVector3D powerBarPos;
    QVector3D powerBarScale;
	
    void render(bool turn);
    void loadShader();
    void setTeam(bool p1Full);
    void setVector(std::vector<Kugel*>* vec);
	void p1Win();
	void p2Win();
	void powerStep();
    void mirrorPowerBarX();

};

#endif // GUI_H
