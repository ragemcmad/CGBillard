#include "lightsources.h"

LightSources::LightSources()
{
    for (uint i = 0; i<4; i++)
        this->isMoving[i] = false;
}
void LightSources::initLights()
{
    this->positions[0] = QVector3D(-40,40,-60);
    this->positions[1] = QVector3D( 40,40,-60);
    this->positions[2] = QVector3D( 40,40, 60);
    this->positions[3] = QVector3D(-40,40, 60);

    this->intensity[0] = QVector3D(50,50,50);//(70,0,0);
    this->intensity[1] = QVector3D(50,50,50);//(0,70,0);
    this->intensity[2] = QVector3D(50,50,50);//(0,0,70);
    this->intensity[3] = QVector3D(50,50,50);//(70,70,70);

    this->animations[0] = new std::vector<Animation>();
    this->animations[1] = new std::vector<Animation>();
    this->animations[2] = new std::vector<Animation>();
    this->animations[3] = new std::vector<Animation>();

    QString p = path::getPath();

    this->loadModel(p.append(QString("models/sphere_high.obj")));
    this->loadShader();
}

void LightSources::loadModel(QString ex_path)
{
    ModelLoader model;
    bool res = model.loadObjectFromFile(ex_path.toStdString());//ex_path.toStdString());
    if (res) {
        // Frage zu erwartende Array-Laeangen ab
        vboLength = model.lengthOfVBO();
        iboLength = model.lengthOfIndexArray();
        // Generiere VBO und Index-Array
        vboData = new GLfloat[vboLength];
        indexData = new GLuint[iboLength];
        model.genVBO(vboData,0,true,true);
        model.genIndexArray(indexData);
    }


    vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    ibo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

    vbo->create();
    vbo->bind();
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo->allocate(vboData, sizeof(GLfloat) * vboLength); // modelloader
    vbo->release();

    ibo->create();
    ibo->bind();
    ibo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo->allocate(indexData, sizeof(GLuint) * iboLength); // modelloader
    ibo->release();
}

void LightSources::loadShader()
{
    // Standardshader
    QOpenGLShaderProgram* standardShaderProg = new QOpenGLShaderProgram();
    QOpenGLShader vertShader(QOpenGLShader::Vertex);
    vertShader.compileSourceFile(":/shader/lightsource.vert");
    standardShaderProg->addShader(&vertShader);
    QOpenGLShader fragShader(QOpenGLShader::Fragment);
    fragShader.compileSourceFile(":/shader/lightsource.frag");
    standardShaderProg->addShader(&fragShader);
    standardShaderProg->link();

    // Sonnenshader
    this->shaderProgram = standardShaderProg;

    glEnable(GL_TEXTURE_2D);
}

void LightSources::render(myCam *cam)
{
    for(int i = 0; i<4;i++)
    {
        shaderProgram->bind();
        vbo->bind();
        ibo->bind();

        int attrVertices = shaderProgram->attributeLocation("vert");

        shaderProgram->enableAttributeArray(attrVertices);

        int unifMatrix = shaderProgram->uniformLocation("matrix");
        int unifMatrixProjection = shaderProgram->uniformLocation("projmatrix");
        int unifMatrixView = shaderProgram->uniformLocation("viewmatrix");
        int unifintensity = shaderProgram->uniformLocation("lightintensity");

        QMatrix4x4 world;
        world.setToIdentity();
        world.translate(this->positions[i]);

        shaderProgram->setUniformValue(unifMatrix, world);
        shaderProgram->setUniformValue(unifMatrixProjection, cam->projMatrix);
        shaderProgram->setUniformValue(unifMatrixView, cam->viewMatrix);
        shaderProgram->setUniformValue(unifintensity, this->intensity[i]);

        int offset = 0;
        size_t stride = 12 * sizeof(GLfloat);
        shaderProgram->setAttributeBuffer(attrVertices, GL_FLOAT, offset, 4, stride);

        glDrawElements(GL_TRIANGLES, iboLength, GL_UNSIGNED_INT, 0);

        shaderProgram->disableAttributeArray(attrVertices);

        ibo->release();
        vbo->release();
    }
}

void LightSources::queueAnimation(QVector3D ziel, int pos, int duration){
    Animation aniNew = Animation(ziel,QVector3D(0,0,0),duration);
    this->animations[pos]->push_back(aniNew);
    if (!this->isMoving[pos])
        this->nextAnimation(pos);
}

void LightSources::nextAnimation(int pos){
    if (!this->animations[pos]->empty())
    {
        this->isMoving[pos] = true;
        Animation ani = this->animations[pos]->at(this->animations[pos]->size()-1);
        this->animations[pos]->pop_back();

        this->moveZiel[pos] = ani.moveZiel;
        this->moveStart[pos] = this->positions[pos];
        this->moveTime[pos] = 0;
        this->moveDuration[pos] = ani.moveDuration;
    }
}

void LightSources::moveStep(int time)
{
    for (int pos=0; pos<4; pos++){
        if(this->isMoving[pos])
        {
            this->moveTime[pos] += time;
            if (this->moveTime[pos] >= this->moveDuration[pos])
            {
                this->isMoving[pos] = false;

                if (!this->animations[pos]->empty())
                    this->nextAnimation(pos);
            }
            else
            {
                QVector3D iamAt = (this->moveZiel[pos]-this->moveStart[pos]) * (-1.0/2.0*cos((this->moveTime[pos]/this->moveDuration[pos])*3.1415926)+0.5)+this->moveStart[pos];
                this->positions[pos] = iamAt;
            }
        }
    }
}

void LightSources::adjustIntensity(int helligkeit){
    intensity[0] = intensity[0] + QVector3D(10*helligkeit,0,0);
    intensity[1] = intensity[1] + QVector3D(0,10*helligkeit,0);
    intensity[2] = intensity[2] + QVector3D(0,0,10*helligkeit);
    intensity[3] = intensity[3] + QVector3D(10*helligkeit,10*helligkeit,10*helligkeit);

}

