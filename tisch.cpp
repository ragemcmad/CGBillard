#include "tisch.h"

Tisch::Tisch()
{

}

Tisch::~Tisch()
{

}

void Tisch::loadShader()
{
    // Standardshader
    QOpenGLShaderProgram* standardShaderProg = new QOpenGLShaderProgram();
    QOpenGLShader vertShader(QOpenGLShader::Vertex);
    vertShader.compileSourceFile(":/shader/v330.vert");
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

    shaderProgram->setUniformValue(unifMatrix,this->worldMatrix);
    shaderProgram->setUniformValue(unifMatrixProjection, cam->projMatrix);
    shaderProgram->setUniformValue(unifMatrixView, cam->viewMatrix);
    shaderProgram->setUniformValueArray(unifLightpos, this->lights->positions,4);
    shaderProgram->setUniformValueArray(unifLightintense, this->lights->intensity,4,1);
    shaderProgram->setUniformValue(unifCamera, cam->getPositionFromViewMatrix(cam->viewMatrix));

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
