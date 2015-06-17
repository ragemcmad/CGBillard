#ifndef KUGEL_H
#define KUGEL_H
#pragma once
#include "gameobject.h"
#include<QOpenGLBuffer>
#include<QOpenGLShaderProgram>
#include<QOpenGLTexture>
#include <vector>


class Kugel : public GameObject
{
private:
    float distanz(QVector3D p1,QVector3D p2);

public:
    Kugel(int id);
    ~Kugel();

    float radius;
    float masse;
    float reibung;
    float konstantReibung;
    int id;
    QVector3D* v;
    QVector3D* pos;
    std::vector<Kugel*>* kugeln;
    std::vector<int>* kugelIndex;
	std::vector<Kugel*>* meineAktiven;
	std::vector<Kugel*>* meineEingelochten;
	
    QMatrix4x4 rotation;
    QVector3D* color;
    void render(myCam* cam);
    void updatePosition();
    bool collisionsCheckKugel(Kugel* k);
    bool collisionsCheckRand();
    void collisionKugel(Kugel* k);
    void collisionRand();
    void gameProgress(float ms);
    bool isMoving();
    void quickSort(int L,int R,std::vector<Kugel*>* kugel, std::vector<int> &list,QVector3D pos);
    void setVector(std::vector<Kugel*>* vec);
    void loadShader();

};

#endif // KUGEL_H
