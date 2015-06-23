#include "tisch.h"

Tisch::Tisch()
{
    for(int i=0;i<16;i++)
    {
        this->waveIsActive[i] = false;
    }
}

Tisch::~Tisch()
{

}

void Tisch::generateWave(float xPosition,float zPosition, float duration)
{
    for(int i=0;i<16;i++)
    {
        if(this->waveIsActive[i] == 0)
        {
            this->waveIsActive[i] = 1;
            this->waveTimeLeft[i] = 0;
            this->waveStartPosX[i] = xPosition;
            this->waveStartPosZ[i] = zPosition;
            this->waveDuration[i] = duration;
            return;
        }
    }
}

void Tisch::loadShader()
{
    // Standardshader
    QOpenGLShaderProgram* standardShaderProg = new QOpenGLShaderProgram();
    QOpenGLShader vertShader(QOpenGLShader::Vertex);
    vertShader.compileSourceFile(":/shader/table.vert");
    standardShaderProg->addShader(&vertShader);
    //QOpenGLShader tcsShader(QOpenGLShader::TessellationControl);
    //tcsShader.compileSourceFile(":/shader/table.tcs");
    //standardShaderProg->addShader(&tcsShader);
    //QOpenGLShader tesShader(QOpenGLShader::TessellationControl);
    //tesShader.compileSourceFile(":/shader/table.tes");
    //standardShaderProg->addShader(&tesShader);
    QOpenGLShader fragShader(QOpenGLShader::Fragment);
    fragShader.compileSourceFile(":/shader/table.frag");
    //qDebug() << shaderProgram.log();
    standardShaderProg->addShader(&fragShader);
    standardShaderProg->link();

    // Sonnenshader
    this->shaderProgram = standardShaderProg;

    // render to cube map shader
    QOpenGLShaderProgram* cubeShaderProg = new QOpenGLShaderProgram();
    QOpenGLShader vertShaderCube(QOpenGLShader::Vertex);
    vertShaderCube.compileSourceFile(":/shader/table.vert");
    //qDebug() << shaderProgram.log();
    cubeShaderProg->addShader(&vertShaderCube);
    //qDebug() << shaderProgram.log();
    QOpenGLShader geomShaderCube(QOpenGLShader::Geometry);
    geomShaderCube.compileSourceFile(":/shader/cube.geom");
    cubeShaderProg->addShader(&geomShaderCube);
    QOpenGLShader fragShaderCube(QOpenGLShader::Fragment);
    fragShaderCube.compileSourceFile(":/shader/table.frag");
    //qDebug() << shaderProgram.log();
    cubeShaderProg->addShader(&fragShaderCube);
    cubeShaderProg->link();

    this->shaderProgramCube = cubeShaderProg;

    glEnable(GL_TEXTURE_2D);
}

void Tisch::render(myCam* cam,int kugel)
{
    QVector3D kugeln[16];
    float kugelnActive[16];
    QVector3D kugelColor[16];
    for(int i = 0; i< 16;i++)
    {
        if(this->waveIsActive[i] == 1)
        {
            this->waveTimeLeft[i]+= 1.0;
            if(this->waveDuration[i] < this->waveTimeLeft[i])
            {
                this->waveIsActive[i] = 0;
            }
        }

        kugeln[i] = *this->kugelPositions->at(i);
        kugelColor[i] = *this->kugelColor->at(i);
        if(*this->kugelActive->at(i) == true)
        {
            kugelnActive[i] = 1;
        }
        else
        {
            kugelnActive[i] = 0;
        }
    }

    if (!isVisible) return;

    QOpenGLShaderProgram* shader = shaderProgram;

    if (cam->isCubeCamera)
        shader = shaderProgramCube;

    shader->bind();
    vbo->bind();
    ibo->bind();

    int attrVertices = shader->attributeLocation("vert");
    //int attrColors = shader->attributeLocation(("color"));
    int attrTexCoords = shader->attributeLocation("texCoord");
    int attrNormals = shader->attributeLocation("normal");


    shader->enableAttributeArray(attrVertices);
    //shader->setAttributeBuffer(attrVertices, GL_FLOAT, 0, 4, 32);
    //shader->enableAttributeArray(attrColors);
    //shader->setAttributeBuffer(attrColors, GL_FLOAT, 16, 4, 32);
    shader->enableAttributeArray(attrTexCoords);
    shader->enableAttributeArray(attrNormals);


    //qDebug() << attrVertices;
    //qDebug() << shaderProgram->log();


    int unifMatrix = shader->uniformLocation("matrix");
    int unifMatrixProjection = shader->uniformLocation("projmatrix");
    int unifMatrixView = shader->uniformLocation("viewmatrix");
    int unifLightpos = shader->uniformLocation("lightpositions");
    int unifLightintense = shader->uniformLocation("lightintensity");
    int unifCamera = shader->uniformLocation("camerapositions");
    int unifWaveA = shader->uniformLocation("WaveActive");
    int unifWaveD = shader->uniformLocation("WaveDuration");
    int unifWaveT = shader->uniformLocation("WaveTime");
    int unifWaveX = shader->uniformLocation("WavePosX");
    int unifWaveZ = shader->uniformLocation("WavePosZ");
    int unifKugelPos = shader->uniformLocation("kugelPosition");
    int unifKugelA = shader->uniformLocation("kugelActive");
    int unifKugelC = shader->uniformLocation("kugelColor");

    shader->setUniformValue(unifMatrix,this->worldMatrix);
    shader->setUniformValue(unifMatrixProjection, cam->projMatrix);
    shader->setUniformValue(unifMatrixView, cam->viewMatrix);
    shader->setUniformValueArray(unifLightpos, this->lights->positions,4);
    shader->setUniformValueArray(unifLightintense, this->lights->intensity,4);
    shader->setUniformValue(unifCamera, cam->getPositionFromViewMatrix(cam->viewMatrix));
    shader->setUniformValueArray(unifWaveA, this->waveIsActive,16,1);
    shader->setUniformValueArray(unifWaveT, this->waveTimeLeft,16,1);
    shader->setUniformValueArray(unifWaveX, this->waveStartPosX,16,1);
    shader->setUniformValueArray(unifWaveZ, this->waveStartPosZ,16,1);
    shader->setUniformValueArray(unifWaveD, this->waveDuration,16,1);
    shader->setUniformValueArray(unifKugelPos, kugeln,16);
    shader->setUniformValueArray(unifKugelA, kugelnActive,16,1);
    shader->setUniformValueArray(unifKugelC, kugelColor,16);

    //QOpenGLFunctions::glActiveTexture(GL_TEXTURE1);
    qTex->bind(1);
    //QOpenGLFunctions::glActiveTexture(GL_TEXTURE0);
    shader->setUniformValue("texture", 1);

    int offset = 0;
    size_t stride = 12 * sizeof(GLfloat);
    shader->setAttributeBuffer(attrVertices, GL_FLOAT, offset, 4, stride);
    offset = 4 * sizeof(GLfloat);
    shader->setAttributeBuffer(attrNormals, GL_FLOAT, offset, 4, stride);
    offset = 8 * sizeof(GLfloat);
    shader->setAttributeBuffer(attrTexCoords, GL_FLOAT, offset, 4, stride);


    glDrawElements(GL_TRIANGLES, iboLength, GL_UNSIGNED_INT, 0);

    shader->disableAttributeArray(attrVertices);
    shader->disableAttributeArray(attrTexCoords);
    shader->disableAttributeArray(attrNormals);


    qTex->release();
    ibo->release();
    vbo->release();

}
