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
public:
    Kugel(int id);
    ~Kugel();

    float radius;
    float masse;
    float reibung;
    float konstantReibung;
    bool eingelocht;
    int id;
    QVector3D* v;
    QVector3D* pos;

    std::vector<Kugel*>* kugeln;
    QMatrix4x4 rotation;

    void updatePosition();
    bool collisionsCheckKugel(Kugel* k);
    bool collisionsCheckRand();
    void collisionKugel(Kugel* k);
    void collisionRand();
    bool gameProgress(float ms);

    void setVector(std::vector<Kugel*>* vec);
    void loadShader();

};

#endif // KUGEL_H
