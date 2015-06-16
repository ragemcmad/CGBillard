#include "tisch.h"

Tisch::Tisch()
{
    for(int i=0;i<16;i++)
    {
        this->waveIsActive[i] = false;
    }
	
	if(this->waveIsActive[0] == 0)
    {
        this->generateWave(0,0, 40);
    }
    if(this->waveIsActive[1] == 0)
    {
        this->generateWave(10,10, 60);
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
    fragShader.compileSourceFile(":/shader/frag330.frag");
    //qDebug() << shaderProgram.log();
    standardShaderProg->addShader(&fragShader);
    standardShaderProg->link();

    // Sonnenshader
    this->shaderProgram = standardShaderProg;

    glEnable(GL_TEXTURE_2D);
}

void Tisch::render(myCam* cam)
{
	
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
    }

    if (!isVisible) return;

    shaderProgram->bind();
    vbo->bind();
    ibo->bind();

    int attrVertices = shaderProgram->attributeLocation("vert");
    //int attrColors = shaderProgram->attributeLocation(("color"));
    int attrTexCoords = shaderProgram->attributeLocation("texCoord");
    int attrNormals = shaderProgram->attributeLocation("normal");


    shaderProgram->enableAttributeArray(attrVertices);
    //shaderProgram->setAttributeBuffer(attrVertices, GL_FLOAT, 0, 4, 32);
    //shaderProgram->enableAttributeArray(attrColors);
    //shaderProgram->setAttributeBuffer(attrColors, GL_FLOAT, 16, 4, 32);
    shaderProgram->enableAttributeArray(attrTexCoords);
    shaderProgram->enableAttributeArray(attrNormals);


    //qDebug() << attrVertices;
    //qDebug() << shaderProgram->log();


    int unifMatrix = shaderProgram->uniformLocation("matrix");
    int unifMatrixProjection = shaderProgram->uniformLocation("projmatrix");
    int unifMatrixView = shaderProgram->uniformLocation("viewmatrix");
    int unifLightpos = shaderProgram->uniformLocation("lightpositions");
    int unifLightintense = shaderProgram->uniformLocation("lightintensity");
    int unifCamera = shaderProgram->uniformLocation("camerapositions");
    int unifWaveA = shaderProgram->uniformLocation("WaveActive");
    int unifWaveD = shaderProgram->uniformLocation("WaveDuration");
    int unifWaveT = shaderProgram->uniformLocation("WaveTime");
    int unifWaveX = shaderProgram->uniformLocation("WavePosX");
    int unifWaveZ = shaderProgram->uniformLocation("WavePosZ");

    shaderProgram->setUniformValue(unifMatrix,this->worldMatrix);
    shaderProgram->setUniformValue(unifMatrixProjection, cam->projMatrix);
    shaderProgram->setUniformValue(unifMatrixView, cam->viewMatrix);
    shaderProgram->setUniformValueArray(unifLightpos, this->lights->positions,4);
    shaderProgram->setUniformValueArray(unifLightintense, this->lights->intensity,4);
    shaderProgram->setUniformValue(unifCamera, cam->getPositionFromViewMatrix(cam->viewMatrix));
    shaderProgram->setUniformValueArray(unifWaveA, this->waveIsActive,16,1);
    shaderProgram->setUniformValueArray(unifWaveT, this->waveTimeLeft,16,1);
    shaderProgram->setUniformValueArray(unifWaveX, this->waveStartPosX,16,1);
    shaderProgram->setUniformValueArray(unifWaveZ, this->waveStartPosZ,16,1);
    shaderProgram->setUniformValueArray(unifWaveD, this->waveDuration,16,1);

    //QOpenGLFunctions::glActiveTexture(GL_TEXTURE1);
    qTex->bind(1);
    //QOpenGLFunctions::glActiveTexture(GL_TEXTURE0);
    shaderProgram->setUniformValue("texture", 1);

    int offset = 0;
    size_t stride = 12 * sizeof(GLfloat);
    shaderProgram->setAttributeBuffer(attrVertices, GL_FLOAT, offset, 4, stride);
    offset = 4 * sizeof(GLfloat);
    shaderProgram->setAttributeBuffer(attrNormals, GL_FLOAT, offset, 4, stride);
    offset = 8 * sizeof(GLfloat);
    shaderProgram->setAttributeBuffer(attrTexCoords, GL_FLOAT, offset, 4, stride);


    glDrawElements(GL_TRIANGLES, iboLength, GL_UNSIGNED_INT, 0);

    shaderProgram->disableAttributeArray(attrVertices);
    shaderProgram->disableAttributeArray(attrTexCoords);
    shaderProgram->disableAttributeArray(attrNormals);


    qTex->release();
    ibo->release();
    vbo->release();

}
