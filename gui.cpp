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


    QMatrix4x4 position;
    position.setToIdentity();
    position.scale(0.05);
    position.translate(8,-17,0);


    this->kugeln[0].loadModel(p.append(QString("models/gui.obj")));
    this->kugeln[0].shaderProgram = standardShaderProg;
    this->kugeln[0].loadTexture(QString::fromStdString(":/textures/kugel10gui.png"));
    this->kugeln[0].setPositionMatrix(position);
    for(int i = 1;i<14;i++)
    {
        this->kugeln[i].shaderProgram = standardShaderProg;
        this->kugeln[i].copyBuffer(&this->kugeln[0]);
        std::stringstream convert;
        convert <<":/textures/kugel"<< i<<"gui.png";
        this->kugeln[i].loadTexture(QString::fromStdString(convert.str()));
    }
    this->players.copyBuffer(&this->kugeln[0]);
    this->players.shaderProgram = standardShaderProg;
    this->players.loadTexture(QString::fromStdString(":/textures/gui.png"));
	
	this->powerLevel = 0;
	
	
	position.setToIdentity();
    position.scale(this->powerBarScale);
    position.translate(this->powerBarPos);
	
	p = path::getPath();
	this->powerBar.copyBuffer(&this->kugeln[0]);
	this->powerBar.loadTexture(QString::fromStdString(":/textures/powerbar.png"));
	
    setTeam(true);
}

void GUI::setTeam(bool p1Full)
{
    this->p1Full = p1Full;
    QMatrix4x4 position;
    position.setToIdentity();
    position.scale(0.05);
    position.translate(-11,17.5,0);

    for(int i = 0; i<7;i++)
    {
        if(this->p1Full== true)
            this->kugeln[i].setPositionMatrix(position);
        else
            this->kugeln[i+7].setPositionMatrix(position);
        position.translate(2,0,0);
    }
    position.translate(6,-34.5,0);
    for(int i = 0; i<7;i++)
    {
        if(this->p1Full== true)
            this->kugeln[i+7].setPositionMatrix(position);
        else
            this->kugeln[i].setPositionMatrix(position);
        position.translate(-2,0,0);
    }
}

void GUI::setVector(std::vector<Kugel*>* vec)
{
    this->kugelnVector = vec;

}

void GUI::render()
{
    glClear(GL_DEPTH_BUFFER_BIT);

    this->players.render();
    for(int i = 0; i< 14;i++)
    {
        if(i<8)
        {
            if(this->kugelnVector->at(i+1)->isVisible == false && this->kugelnVector->at(i+1)->id ==i+1)
            {
                this->kugeln[i].render();
            }
        }
        else
        {
            if(this->kugelnVector->at(i+2)->isVisible == false && this->kugelnVector->at(i+2)->id ==i+2)
            {
                this->kugeln[i].render();
            }
        }
    }
}

void GUI::p1Win()
{
	
}

void GUI::p2Win()
{
	
}

void GUI::powerStep()
{
	this->powerLevel = (this->powerLevel+this->powerChange)%this->maxPower;
}

