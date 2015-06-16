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
	GuiTexture winSign;
	GuiTexture powerBar;
    std::vector<Kugel*>* kugelnVector;
    bool p1Full;
	float powerLevel;
	float const maxPower = 100;
    float const powerChange = 0.5;
	
    QVector3D const powerBarPos = QVector3D(0.95,0.2,0);
    QVector3D const powerBarScale = QVector3D(0.03,0.3,0);
	
    void render();
    void loadShader();
    void setTeam(bool p1Full);
    void setVector(std::vector<Kugel*>* vec);
	void p1Win();
	void p2Win();
	void powerStep();

};

#endif // GUI_H
