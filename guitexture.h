#ifndef GUITEXTURE_H
#define GUITEXTURE_H

#include "gameobject.h"
#include<QOpenGLBuffer>
#include<QOpenGLShaderProgram>
#include<QOpenGLTexture>

class GuiTexture : public GameObject
{
public:
    GuiTexture();

    void render();
    void copyShader(QOpenGLShaderProgram* shader);
    void setPositionMatrix(QMatrix4x4 matrix);
    void copyBuffer(GuiTexture* guielement);
    void setTexturePoints(QVector3D buttonLeft,QVector3D topRight);
};

#endif // GUITEXTURE_H
