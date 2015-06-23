#include "gameobject.h"

GameObject::GameObject()
{
    isVisible = true;
}

GameObject::~GameObject()
{
}


void GameObject::render(myCam* cam,int kugel)
{
    if (!isVisible) return;

    QOpenGLShaderProgram* shader = shaderProgram;

    if (cam->isCubeCamera)
        shader = shaderProgramCube;

    shader->bind();
    vbo->bind();
    ibo->bind();

    int attrVertices = shader->attributeLocation("vert");
    //int attrColors = shaderProgram->attributeLocation(("color"));
    int attrTexCoords = shader->attributeLocation("texCoord");
    int attrNormals = shader->attributeLocation("normal");


    shader->enableAttributeArray(attrVertices);
    //shader->setAttributeBuffer(attrVertices, GL_FLOAT, 0, 4, 32);
    //shader->enableAttributeArray(attrColors);
    //shader->setAttributeBuffer(attrColors, GL_FLOAT, 16, 4, 32);
    shader->enableAttributeArray(attrTexCoords);
    shader->enableAttributeArray(attrNormals);


    //qDebug() << attrVertices;
    //qDebug() << shader->log();


    int unifMatrix = shader->uniformLocation("matrix");
    int unifMatrixWVP = shader->uniformLocation("worldviewproj");
    int unifLightpos = shader->uniformLocation("lightpositions");
    int unifLightintense = shader->uniformLocation("lightintensity");
    int unifCamera = shader->uniformLocation("camerapositions");

    shader->setUniformValue(unifMatrix,this->worldMatrix);
    shader->setUniformValue(shader->uniformLocation("matrixIT"),this->worldMatrix.inverted().transposed());
    shader->setUniformValue(unifMatrixWVP, cam->projMatrix * cam->viewMatrix * this->worldMatrix);
    shader->setUniformValueArray(unifLightpos, this->lights->positions,4);
    shader->setUniformValueArray(unifLightintense, this->lights->intensity,4);
    shader->setUniformValue(unifCamera, cam->getPositionFromViewMatrix(cam->viewMatrix));

    if (cam->isCubeCamera)
    {
        int unifCubeProj = shader->uniformLocation("cubeProj");
        shader->setUniformValue(unifCubeProj, cam->projMatrix);

        int unifCubeView = shader->uniformLocation("cubeViews");
        shader->setUniformValueArray(unifCubeView, cam->viewMatrixCube, 6);
    }

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

void GameObject::loadLights(LightSources* lights)
{
    this->lights = lights;
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


    // render to cube map shader
    QOpenGLShaderProgram* cubeShaderProg = new QOpenGLShaderProgram();
    QOpenGLShader vertShaderCube(QOpenGLShader::Vertex);
    vertShaderCube.compileSourceFile(":/shader/v330.vert");
    //qDebug() << shaderProgram.log();
    cubeShaderProg->addShader(&vertShaderCube);
    //qDebug() << shaderProgram.log();
    QOpenGLShader geomShaderCube(QOpenGLShader::Geometry);
    geomShaderCube.compileSourceFile(":/shader/cube.geom");
    cubeShaderProg->addShader(&geomShaderCube);
    QOpenGLShader fragShaderCube(QOpenGLShader::Fragment);
    fragShaderCube.compileSourceFile(":/shader/frag330.frag");
    //qDebug() << shaderProgram.log();
    cubeShaderProg->addShader(&fragShaderCube);
    cubeShaderProg->link();

    this->shaderProgramCube = cubeShaderProg;

    glEnable(GL_TEXTURE_2D);
}
