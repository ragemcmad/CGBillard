#include "guitexture.h"

GuiTexture::GuiTexture()
{

}

void GuiTexture::setPositionMatrix(QMatrix4x4 matrix)
{
    this->worldMatrix = matrix;
}

void GuiTexture::copyShader(QOpenGLShaderProgram* shader)
{
    this->shaderProgram = shader;
}

void GuiTexture::copyBuffer(GuiTexture* guielement){
    this->vbo = guielement->vbo;
    this->ibo = guielement->ibo;
    this->vboLength = guielement->vboLength;
    this->iboLength = guielement->iboLength;
}

void GuiTexture::setTexturePoints(QVector3D bottomLeft,QVector3D topRight)
{
    QMatrix4x4 position;
    float deltaScaleX = (topRight.x()-bottomLeft.x())/2;
    float deltaScaleY = (topRight.y()-bottomLeft.y())/2;
    float midx = (topRight.x()+bottomLeft.x())/2;
    float midy = (topRight.y()+bottomLeft.y())/2;

    position.scale(deltaScaleX,deltaScaleY,1);
    position.translate(midx/deltaScaleX,midy/deltaScaleY,0);

    this->setPositionMatrix(position);
}


void GuiTexture::render()
{
    if (!isVisible) return;

    shaderProgram->bind();
    vbo->bind();
    ibo->bind();

    int attrVertices = shaderProgram->attributeLocation("vert");
    int attrTexCoords = shaderProgram->attributeLocation("texCoord");
    int attrNormals = shaderProgram->attributeLocation("normal");


    shaderProgram->enableAttributeArray(attrVertices);
    shaderProgram->enableAttributeArray(attrTexCoords);
    shaderProgram->enableAttributeArray(attrNormals);


    qTex->bind(1);
    shaderProgram->setUniformValue("texture", 1);

    int offset = 0;
    size_t stride = 12 * sizeof(GLfloat);
    shaderProgram->setAttributeBuffer(attrVertices, GL_FLOAT, offset, 4, stride);
    offset = 4 * sizeof(GLfloat);
    shaderProgram->setAttributeBuffer(attrNormals, GL_FLOAT, offset, 4, stride);
    offset = 8 * sizeof(GLfloat);
    shaderProgram->setAttributeBuffer(attrTexCoords, GL_FLOAT, offset, 4, stride);

    int unifMatrix = shaderProgram->uniformLocation("matrix");
    shaderProgram->setUniformValue(unifMatrix,this->worldMatrix);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDrawElements(GL_TRIANGLES, iboLength, GL_UNSIGNED_INT, 0);


    shaderProgram->disableAttributeArray(attrVertices);
    shaderProgram->disableAttributeArray(attrTexCoords);
    shaderProgram->disableAttributeArray(attrNormals);

    qTex->release();
    ibo->release();
    vbo->release();
}
