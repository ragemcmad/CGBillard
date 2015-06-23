#include "gui.h"

GUI::GUI()
{
    maxPower = 100;
    powerChange = 0.5;
    this->p1Full = NULL;
    this->powerBarPos = QVector3D(-0.95,0.0,0);
    this->powerBarScale  = QVector3D(0.04,0.4,0);
}

GUI::~GUI()
{
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
    this->kugeln[0].loadTexture(QString::fromStdString(":/textures/kugel1gui.png"));
    this->kugeln[0].setPositionMatrix(position);
    for(int i = 1;i<14;i++)
    {
        this->kugeln[i].shaderProgram = standardShaderProg;
        this->kugeln[i].copyBuffer(&this->kugeln[0]);
        std::stringstream convert;
        if(i<7)
        {
            convert <<":/textures/kugel"<< i+1<<"gui.png";
        }
        else
        {
            convert <<":/textures/kugel"<< i+2<<"gui.png";
        }
        this->kugeln[i].loadTexture(QString::fromStdString(convert.str()));
    }
    this->players1.copyBuffer(&this->kugeln[0]);
    this->players1.shaderProgram = standardShaderProg;
    this->players1.loadTexture(QString::fromStdString(":/textures/guiP1aktiv.png"));
    this->players2.copyBuffer(&this->kugeln[0]);
    this->players2.shaderProgram = standardShaderProg;
    this->players2.loadTexture(QString::fromStdString(":/textures/guiP2aktiv.png"));

	this->powerLevel = 0;
	
	position.setToIdentity();
    position.scale(this->powerBarScale);
    position.translate(this->powerBarPos);
	
	p = path::getPath();
	this->powerBar.setPositionMatrix(position);
	this->powerBar.copyBuffer(&this->kugeln[0]);
	this->powerBar.loadTexture(QString::fromStdString(":/textures/powerbar.png"));
    this->powerBar.shaderProgram = standardShaderProg;
	
	position.setToIdentity();
    position.scale(0.4);
	
	this->winSign.setPositionMatrix(position);
	this->winSign.copyBuffer(&this->kugeln[0]);
	this->winSign.isVisible = false;
    this->winSign.shaderProgram = standardShaderProg;
}

void GUI::setTeam(bool p1Full)
{
    this->p1Full = p1Full;
    QMatrix4x4 position;
    position.setToIdentity();
    position.scale(0.039,0.05,1);
    position.translate(-15,17.5,0);

    for(int i = 0; i<7;i++)
    {
        if(this->p1Full== true)
            this->kugeln[i].setPositionMatrix(position);
        else
            this->kugeln[i+7].setPositionMatrix(position);
        position.translate(2,0,0);
    }
    position.translate(16,-34.5,0);
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

void GUI::render(bool turn)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    powerStep();
    if (turn)
        this->players2.render();
    else
        this->players1.render();
    for(int i = 0; i< 14;i++)
    {
        if(i<7)
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
	this->winSign.render();
	this->powerBar.render();
}

void GUI::p1Win()
{
	QString p = path::getPath();
    this->winSign.loadTexture(QString::fromStdString(":/textures/p1win.png"));
	this->winSign.isVisible = true;
    this->powerBar.isVisible = false;
}

void GUI::p2Win()
{
	QString p = path::getPath();
    this->winSign.loadTexture(QString::fromStdString(":/textures/p2win.png"));
	this->winSign.isVisible = true;
    this->powerBar.isVisible = false;
}

void GUI::powerStep()
{
    this->powerLevel += this->powerChange;
    if(this->powerLevel > this->maxPower)
    {
        this->powerLevel = 0;
    }

    effectivePower = (sin(((this->powerLevel/this->maxPower)+1)*3.1415926)+1);

    this->powerBar.setTexturePoints(this->powerBarPos,
                                    QVector3D(this->powerBarPos.x()+this->powerBarScale.x(),
                                              this->powerBarPos.y()+this->powerBarScale.y()*(this->effectivePower),
                                              0)
                                    );
                                    /*
                                    QVector3D(this->powerBarPos.x()+this->powerBarScale.x(),
                                              this->powerBarPos.y()+this->powerBarScale.y()*(1-(this->maxPower-this->powerLevel)/this->maxPower),
                                              0)
                                    );
                                    */
}

void GUI::mirrorPowerBarX()
{
    powerBarPos.setX(-(this->powerBarPos.x()));
}
