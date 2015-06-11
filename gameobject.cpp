#include "gameobject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{

}


void GameObject::render(myCam* cam)
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
    int uniftimer = shaderProgram->uniformLocation("timer");


    shaderProgram->setUniformValue(unifMatrix,this->worldMatrix);
    shaderProgram->setUniformValue(unifMatrixProjection, cam->projMatrix);
    shaderProgram->setUniformValue(unifMatrixView, cam->viewMatrix);

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

void GameObject::loadModel(QString ex_path)
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

void GameObject::copyBuffer(GameObject* sso){
    this->vbo = sso->vbo;
    this->ibo = sso->ibo;
    this->vboLength = sso->vboLength;
    this->iboLength = sso->iboLength;
}

void GameObject::loadTexture(QString path)
{
    glEnable(GL_TEXTURE_2D);
    qTex = new QOpenGLTexture(QImage(path).mirrored());
    qTex->setWrapMode(QOpenGLTexture::Repeat);
    qTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    qTex->setMagnificationFilter(QOpenGLTexture::Linear);
}

void GameObject::loadShader()
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
