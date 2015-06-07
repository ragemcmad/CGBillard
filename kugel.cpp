#include "kugel.h"
#include <math.h>

Kugel::Kugel(int id)
{
    this->reibung = 1;//0.9999f;
    this->konstantReibung = 0;//0.0001f;
    this->masse = 1;
    this->radius = 1;
    this->v = new QVector3D();
    this->v->setX(0);
    this->v->setY(0);
    this->v->setZ(0);
    this->id = id;
    this->pos = new QVector3D();
    this->rotation.setToIdentity();
}

Kugel::~Kugel()
{

}


void Kugel::loadShader()
{
    // Standardshader
    QOpenGLShaderProgram* standardShaderProg = new QOpenGLShaderProgram();
    QOpenGLShader vertShader(QOpenGLShader::Vertex);
    vertShader.compileSourceFile(":/shader/v330.vert");
    //qDebug() << shaderProgram.log();
    standardShaderProg->addShader(&vertShader);
    //qDebug() << shaderProgram.log();
    QOpenGLShader fragShader(QOpenGLShader::Fragment);
    fragShader.compileSourceFile(":/shader/frag330.frag");
    //qDebug() << shaderProgram.log();
    standardShaderProg->addShader(&fragShader);
    standardShaderProg->link();

    // Sonnenshader
    this->shaderProgram = standardShaderProg;

    glEnable(GL_TEXTURE_2D);

}

void Kugel::setVector(std::vector<Kugel*>* vec)
{
    this->kugeln = vec;
}

bool Kugel::collisionsCheckKugel(Kugel* k)
{
    float x1 = this->worldMatrix.column(3).x();
    float y1 = this->worldMatrix.column(3).y();
    float z1 = this->worldMatrix.column(3).z();


    float x2 = k->worldMatrix.column(3).x();
    float y2 = k->worldMatrix.column(3).y();
    float z2 = k->worldMatrix.column(3).z();

    float distanz = sqrt(pow(x1-x2,2)+pow(y1-y2,2)+pow(z1-z2,2));
    if(distanz <= k->radius + this->radius)
    {
        return true;
    }
    return false;
}

bool Kugel::collisionsCheckRand()
{
    float x = this->pos->x();
    float z = this->pos->z();

    if(x>17.5 || x<-17.5)
    {
        if(x>17.5)
        {
            this->pos->setX(17.5f);
        }
        else
        {
            this->pos->setX(-17.5f);
        }
        this->v->setX(-this->v->x());
        QVector3D vRichtung;
        vRichtung.setX(this->v->x());
        vRichtung.setY(this->v->y());
        vRichtung.setZ(this->v->z());

        vRichtung.normalize();
        this->v->setX(this->v->x()*pow(reibung,3)-vRichtung.x()*konstantReibung);
        this->v->setZ(this->v->z()*pow(reibung,3)-vRichtung.z()*konstantReibung);

    }

    if(z>36||z<-36)
    {
        if(z>36)
        {
            this->pos->setZ(36);
        }
        else
        {
            this->pos->setZ(-36);
        }
        this->v->setZ(-this->v->z());
        QVector3D vRichtung;
        vRichtung.setX(this->v->x());
        vRichtung.setY(this->v->y());
        vRichtung.setZ(this->v->z());

        vRichtung.normalize();
        this->v->setX(this->v->x()*pow(reibung,3)-vRichtung.x()*konstantReibung);
        this->v->setZ(this->v->z()*pow(reibung,3)-vRichtung.z()*konstantReibung);

    }

    return true;
}

void Kugel::updatePosition()
{
    this->pos->setX(this->worldMatrix.column(3).x());
    this->pos->setY(this->worldMatrix.column(3).y());
    this->pos->setZ(this->worldMatrix.column(3).z());
}

void Kugel::collisionKugel(Kugel *kugel)
{
    float v1x = this->v->x();
    float v1y = this->v->y();
    float v1z = this->v->z();
    float m1 = this->masse;

    float v2x = kugel->v->x();
    float v2y = kugel->v->y();
    float v2z = kugel->v->z();
    float m2 = kugel->masse;

    float deltaX = kugel->pos->x()-this->pos->x();
    float deltaY = kugel->pos->y()-this->pos->y();
    float deltaZ = kugel->pos->z()-this->pos->z();

    float d2 = pow(deltaX,2)+pow(deltaY,2)+pow(deltaZ,2);

    float e =     (m1*(v1x*deltaX + v1y*deltaY + v1z*deltaZ) + 2 * m2*(v2x*deltaX + v2y*deltaY + v2z*deltaZ) - (v1x*deltaX + v1y*deltaY + v1z*deltaZ)*m2) / (d2*(m2 + m1));
    float f = (2 * m1*(v1x*deltaX + v1y*deltaY + v1z*deltaZ) +     m2*(v2x*deltaX + v2y*deltaY + v2z*deltaZ) - (v2x*deltaX + v2y*deltaY + v2z*deltaZ)*m1) / (d2*(m2 + m1));

    float v1xOut = e*deltaX - ((v1z*deltaX - v1x*deltaZ)*deltaZ - (v1x*deltaY - v1y*deltaX)*deltaY) / d2;
    float v1yOut = e*deltaY - ((v1x*deltaY - v1y*deltaX)*deltaX - (v1y*deltaZ - v1z*deltaY)*deltaZ) / d2;
    float v1zOut = e*deltaZ - ((v1y*deltaZ - v1z*deltaY)*deltaY - (v1z*deltaX - v1x*deltaZ)*deltaX) / d2;

    float v2xOut = f*deltaX - ((v2z*deltaX - v2x*deltaZ)*deltaZ - (v2x*deltaY - v2y*deltaX)*deltaY) / d2;
    float v2yOut = f*deltaY - ((v2x*deltaY - v2y*deltaX)*deltaX - (v2y*deltaZ - v2z*deltaY)*deltaZ) / d2;
    float v2zOut = f*deltaZ - ((v2y*deltaZ - v2z*deltaY)*deltaY - (v2z*deltaX - v2x*deltaZ)*deltaX) / d2;

    kugel->v->setX(v2xOut);
    kugel->v->setY(v2yOut);
    kugel->v->setZ(v2zOut);

    this->v->setX(v1xOut);
    this->v->setY(v1yOut);
    this->v->setZ(v1zOut);

}

void Kugel::gameProgress(float ms)
{
    for(int j = 0; j< 10;j++)
    {
        this->collisionsCheckRand();

        for(int i = 0; i< this->kugeln->size();i++)
        {
            if(this->kugeln->at(i)->id != this->id)
            {
                if(this->collisionsCheckKugel(this->kugeln->at(i)))
                {
                    //setze die kugeln auseinander

                    this->collisionKugel(this->kugeln->at(i));
                }
            }
        }

        QMatrix4x4 rot;
        rot.setToIdentity();
        rot.rotate(this->v->z()*2*3.1415f,1,0,0);
        this->rotation =  rot*this->rotation ;
        rot.setToIdentity();
        rot.rotate(-this->v->x()*2*3.1415f,0,0,1);
        this->rotation = rot*this->rotation;

        this->worldMatrix.setToIdentity();
        this->worldMatrix.translate(this->v->x()*0.1+this->pos->x(),this->v->y()*0.1+this->pos->y(),this->v->z()*0.1+this->pos->z());




        this->worldMatrix = this->worldMatrix * this->rotation;


        QVector3D vRichtung;
        vRichtung.setX(this->v->x());
        vRichtung.setY(this->v->y());
        vRichtung.setZ(this->v->z());

        vRichtung.normalize();
        this->v->setX(this->v->x()*reibung-vRichtung.x()*konstantReibung);
        this->v->setZ(this->v->z()*reibung-vRichtung.z()*konstantReibung);

        this->updatePosition();


    }
}


