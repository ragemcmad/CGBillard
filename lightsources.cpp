#include "lightsources.h"

LightSources::LightSources()
{

}
void LightSources::initLights()
{
    this->positions[0] = QVector3D(-20,50,-30);
    this->positions[1] = QVector3D(+20,50,-30);
    this->positions[2] = QVector3D(+20,50,+30);
    this->positions[3] = QVector3D(-20,50,+30);
    this->intensity[0] = QVector3D(30,0,0);
    this->intensity[1] = QVector3D(0,30,0);
    this->intensity[2] = QVector3D(0,0,30);
    this->intensity[3] = QVector3D(30,30,30);

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
