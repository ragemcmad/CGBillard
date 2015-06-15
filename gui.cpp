#include "gui.h"

GUI::GUI()
{
    this->p1Full = NULL;
}

void GUI::loadShader()
{


    // Standardshader
    QOpenGLShaderProgram* standardShaderProg = new QOpenGLShaderProgram();
    QOpenGLShader vertShader(QOpenGLShader::Vertex);
    vertShader.compileSourceFile(":/shader/gui.vert");
    //qDebug() << shaderProgram.log();
    standardShaderProg->addShader(&vertShader);
    //qDebug() << shaderProgram.log();
    QOpenGLShader fragShader(QOpenGLShader::Fragment);
    fragShader.compileSourceFile(":/shader/gui.frag");
    //qDebug() << shaderProgram.log();
    standardShaderProg->addShader(&fragShader);
    standardShaderProg->link();
    glEnable(GL_TEXTURE_2D);

    QString p = path::getPath();


    this->kugeln[0].loadModel(p.append(QString("models/gui.obj")));
    this->kugeln[0].shaderProgram = standardShaderProg;
    for(int i = 1;i<15;i++)
    {
        this->kugeln[i].copyBuffer(&this->kugeln[0]);
        std::stringstream convert;
        convert <<":/textures/kugel"<< i<<".png";
        this->kugeln[i].loadTexture(QString::fromStdString(convert.str()));
    }
    this->players.copyBuffer(&this->kugeln[0]);
    this->players.shaderProgram = standardShaderProg;
    this->players.loadTexture(QString::fromStdString(":/textures/gui.png"));

}

void GUI::setTeam(bool p1Full)
{
    this->p1Full = p1Full;
}

void GUI::setVector(std::vector<Kugel*>* vec)
{
    this->kugelnVector = vec;
}

void GUI::render()
{
    glClear(GL_DEPTH_BUFFER_BIT);

    this->players.render();

}
