#include "sonnensystemobjekt.h"
#include <qdebug.h>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <QOpenGLFunctions>

void SonnensystemObjekt::loadVertices()
{

    /* Deklaration der Attribute */
    // Eckpunkte
    // (1 Rechteck mit 4 Eckpunkten mit je 4 Koordinaten und 4 Farbkanalen)
    GLfloat vertices[8*(4+4)];
    // Verwendete Elemente (1 Rechteck, das durch 2 Dreiecke dargestellt wird)
    GLuint indices[36]; // fur groe Meshes lieber GLuint
    // Handle fur VBO (Eckpunkte + Farben)
    //GLuint vboHandle;
    // Handle fur BO der zu zeichnenden VBO-Elemente

    //GLuint indicesHandle;
    /* Erzeugen der Geometrie (gekurzt) */
    // 1. Vertex, Position
    vertices[0] = 1.0f;
    vertices[1] = -1.0f;
    vertices[2] = 1.0f;
    vertices[3] = 1.0f; // 4. Komponente, immer 1
    // 1. Vertex, Farbe
    vertices[4] = 1.0f;
    vertices[5] = 1.0f;
    vertices[6] = 1.0f;
    vertices[7] = 1.0f; // 4. Komponente, immer 1
    // 2. Vertex, Position
    vertices[8] = 1.0f;
    vertices[9] = 1.0f;
    vertices[10] = 1.0f;
    vertices[11] = 1.0f; // 4. Komponente, immer 1
    // 2. Vertex, Farbe
    vertices[12] = 1.0f;
    vertices[13] = 0.0f;
    vertices[14] = 1.0f;
    vertices[15] = 1.0f; // 4. Komponente, immer 1
    // 3. Vertex, Position
    vertices[16] = -1.0f;
    vertices[17] = 1.0f;
    vertices[18] = 1.0f;
    vertices[19] = 1.0f; // 4. Komponente, immer 1
    // 3. Vertex, Farbe
    vertices[20] = 1.0f;
    vertices[21] = 1.0f;
    vertices[22] = 0.0f;
    vertices[23] = 1.0f; // 4. Komponente, immer 1
    // 4. Vertex, Position
    vertices[24] = -1.0f;
    vertices[25] = -1.0f;
    vertices[26] = 1.0f;
    vertices[27] = 1.0f; // 4. Komponente, immer 1
    // 4. Vertex, Farbe
    vertices[28] = 0.0f;
    vertices[29] = 1.0f;
    vertices[30] = 1.0f;
    vertices[31] = 1.0f; // 4. Komponente, immer 1

    // 5. Vertex, Position
    vertices[32] = 1.0f;
    vertices[33] = -1.0f;
    vertices[34] = -1.0f;
    vertices[35] = 1.0f; // 4. Komponente, immer 1
    // 5. Vertex, Farbe
    vertices[36] = 1.0f;
    vertices[37] = 1.0f;
    vertices[38] = 1.0f;
    vertices[39] = 1.0f; // 4. Komponente, immer 1
    // 6. Vertex, Position
    vertices[40] = 1.0f;
    vertices[41] = 1.0f;
    vertices[42] = -1.0f;
    vertices[43] = 1.0f; // 4. Komponente, immer 1
    // 6. Vertex, Farbe
    vertices[44] = 1.0f;
    vertices[45] = 0.0f;
    vertices[46] = 1.0f;
    vertices[47] = 1.0f; // 4. Komponente, immer 1
    // 7. Vertex, Position
    vertices[48] = -1.0f;
    vertices[49] = 1.0f;
    vertices[50] = -1.0f;
    vertices[51] = 1.0f; // 4. Komponente, immer 1
    // 7. Vertex, Farbe
    vertices[52] = 1.0f;
    vertices[53] = 1.0f;
    vertices[54] = 0.0f;
    vertices[55] = 1.0f; // 4. Komponente, immer 1
    // 8. Vertex, Position
    vertices[56] = -1.0f;
    vertices[57] = -1.0f;
    vertices[58] = -1.0f;
    vertices[59] = 1.0f; // 4. Komponente, immer 1
    // 8. Vertex, Farbe
    vertices[60] = 0.0f;
    vertices[61] = 1.0f;
    vertices[62] = 1.0f;
    vertices[63] = 1.0f; // 4. Komponente, immer 1

    // Initialisiere Elemente
    //front
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 2;
    indices[4] = 3;
    indices[5] = 0;
    //back
    indices[6]=  4;
    indices[7]=  7;
    indices[8]=  6;
    indices[9]=  6;
    indices[10]= 5;
    indices[11]= 4;
    //right
    indices[12]= 4;
    indices[13]= 5;
    indices[14]= 0;
    indices[15]= 0;
    indices[16]= 5;
    indices[17]= 1;
    //left
    indices[18]= 3;
    indices[19]= 2;
    indices[20]= 6;
    indices[21]= 6;
    indices[22]= 7;
    indices[23]= 3;
    //top
    indices[24]= 1;
    indices[25]= 5;
    indices[26]= 6;
    indices[27]= 6;
    indices[28]= 2;
    indices[29]= 1;
    //bot
    indices[30]= 4;
    indices[31]= 0;
    indices[32]= 3;
    indices[33]= 3;
    indices[34]= 7;
    indices[35]= 4;


    vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    ibo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

    vbo->create();
    vbo->bind();
    vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vbo->allocate(vertices,sizeof(vertices));
    vbo->release();

    ibo->create();
    ibo->bind();
    ibo->setUsagePattern(QOpenGLBuffer::StaticDraw);
    ibo->allocate(indices, sizeof(indices));
    ibo->release();

    this->iboLength = 36;
    this->vboLength = 8;
    //qDebug() << sizeof(vertices)<<" "<< sizeof(indices);
}

void SonnensystemObjekt::loadModel(QString ex_path, bool normals)
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
    else {
        qDebug()<< "Fail2Load: "<<ex_path;
        this->loadVertices();
        return;
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

void SonnensystemObjekt::copyBuffer(SonnensystemObjekt* sso){
    this->vbo = sso->vbo;
    this->ibo = sso->ibo;
    this->vboLength = sso->vboLength;
    this->iboLength = sso->iboLength;
}

void SonnensystemObjekt::loadTexture(QString path)
{
    glEnable(GL_TEXTURE_2D);
    qTex = new QOpenGLTexture(QImage(path).mirrored());
    qTex->setWrapMode(QOpenGLTexture::Repeat);
    qTex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    qTex->setMagnificationFilter(QOpenGLTexture::Linear);
}

void SonnensystemObjekt::buildSystem(){

    // Standardshader
    QOpenGLShaderProgram* standardShaderProg = new QOpenGLShaderProgram();
    QOpenGLShader vertShader(QOpenGLShader::Vertex);
    vertShader.compileSourceFile(":/shader/v330.vert");
    //qDebug() << shaderProgram.log();
    standardShaderProg->addShader(&vertShader);
    //qDebug() << shaderProgram.log();
    QOpenGLShader fragShader(QOpenGLShader::Fragment);
    fragShader.compileSourceFile(":/shader/frag330.frag");
    standardShaderProg->addShader(&fragShader);
    standardShaderProg->link();
    qDebug() << standardShaderProg->log();

    // Sonnenshader
    QOpenGLShaderProgram* sonnenShaderProg = new QOpenGLShaderProgram();
    sonnenShaderProg->addShader(&vertShader);
    QOpenGLShader sunShader(QOpenGLShader::Fragment);
    sunShader.compileSourceFile(":/shader/sunshader.frag");
    sonnenShaderProg->addShader(&sunShader);
    sonnenShaderProg->link();
    this->setShaderProgram(sonnenShaderProg);
    this->isSun = true;
    qDebug() << sonnenShaderProg->log();

    glEnable(GL_TEXTURE_2D);
    this->qTexWave = new QOpenGLTexture(QImage(QString(":textures/wave.jpg")).mirrored());
    this->qTexWave->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    this->qTexWave->setMagnificationFilter(QOpenGLTexture::Linear);


    this->winkelSpeedSelf = 0.1;
    //this->loadVertices();
    this->loadModel(QString("C:/Users/Olli/Dropbox/Vorlesungsfolien/CG/praktikum/P4/qtp4/models/sphere_low.obj"), false);
    this->loadTexture(QString(":/textures/sunmap.jpg"));
    int abst = 3;
    SonnensystemObjekt* merkur = new SonnensystemObjekt();
        merkur->dist = abst;
        merkur->winkelSpeedSelf = 1.0;
        merkur->winkelSpeedParent = 5.0;
        merkur->loadVertices();
        //merkur->loadModel(QString("C:/Users/thoma_000/Documents/QT/qtp2/models/sphere_low.obj"),false);
        merkur->loadTexture(QString(":/textures/mercurymap.jpg"));
        merkur->copyBuffer(this);
        merkur->setShaderProgram(standardShaderProg);
    SonnensystemObjekt* venus = new SonnensystemObjekt();
        venus->dist = abst*2;
        venus->winkelSpeedSelf = 2;
        venus->winkelSpeedParent = 0.7;
        //venus->loadVertices();
        //venus->loadModel(QString("H:/CG/qtp2/models/sphere_low.obj"), false);
        venus->loadTexture(QString(":/textures/venusmap.jpg"));
        venus->copyBuffer(this);
        venus->setShaderProgram(standardShaderProg);
    SonnensystemObjekt* erde = new SonnensystemObjekt();
        erde->dist = abst*3;
        erde->winkelSpeedSelf = 3.0;
        erde->winkelSpeedParent = 0.6;
        //erde->loadVertices();
        //erde->loadModel(QString("H:/CG/qtp2/models/sphere_low.obj"), false);
        erde->loadTexture(QString(":/textures/earthmap1k.jpg"));
        erde->copyBuffer(this);
        erde->setShaderProgram(standardShaderProg);
    SonnensystemObjekt* mars = new SonnensystemObjekt();
        mars->dist = abst*4;
        mars->winkelSpeedSelf = 4;
        mars->winkelSpeedParent = 0.5;
        //mars->loadVertices();
        //mars->loadModel(QString("H:/CG/qtp2/models/sphere_low.obj"), false);
        mars->loadTexture(QString(":/textures/mars_1k_color.jpg"));
        mars->copyBuffer(this);
        mars->setShaderProgram(standardShaderProg);
    SonnensystemObjekt* jupiter = new SonnensystemObjekt();
        jupiter->dist = abst*5;
        jupiter->winkelSpeedSelf = 5;
        jupiter->winkelSpeedParent = 0.4;
        //jupiter->loadVertices();
        //jupiter->loadModel(QString("H:/CG/qtp2/models/sphere_low.obj"), false);
        jupiter->copyBuffer(this);
        jupiter->loadTexture(QString(":/textures/jupitermap.jpg"));
        jupiter->setShaderProgram(standardShaderProg);
    SonnensystemObjekt* saturn = new SonnensystemObjekt();
        saturn->dist = abst*6;
        saturn->winkelSpeedSelf = 6;
        saturn->winkelSpeedParent = 0.3;
        //saturn->loadVertices();
        //saturn->loadModel(QString("H:/CG/qtp2/models/sphere_low.obj"), false);
        saturn->copyBuffer(this);
        saturn->loadTexture(QString(":/textures/saturnmap.jpg"));
        saturn->setShaderProgram(standardShaderProg);
    SonnensystemObjekt* uranus = new SonnensystemObjekt();
        uranus->dist = abst*7;
        uranus->winkelSpeedSelf = 7;
        uranus->winkelSpeedParent = 0.2;
        //uranus->loadVertices();
        //uranus->loadModel(QString("H:/CG/qtp2/models/sphere_low.obj"), false);
        uranus->copyBuffer(this);
        uranus->loadTexture(QString(":/textures/uranusmap.jpg"));
        uranus->setShaderProgram(standardShaderProg);
    SonnensystemObjekt* neptun = new SonnensystemObjekt();
        neptun->dist = abst*8;
        neptun->winkelSpeedSelf = 8;
        neptun->winkelSpeedParent = 0.01;
        //neptun->loadVertices();
        //neptun->loadModel(QString("H:/CG/qtp2/models/sphere_low.obj"), false);
        neptun->copyBuffer(this);
        neptun->loadTexture(QString(":/textures/neptunemap.jpg"));
        neptun->setShaderProgram(standardShaderProg);
    SonnensystemObjekt* erdmond = new SonnensystemObjekt();
        erdmond->dist = 2;
        erdmond->winkelSpeedSelf = 8;
        erdmond->winkelSpeedParent = 8;
        //erdmond->loadVertices();
        //erdmond->loadModel(QString("H:/CG/qtp2/models/sphere_low.obj"), false);
        erdmond->copyBuffer(this);
        erdmond->loadTexture(QString(":/textures/moonmap1k.jpg"));
        erdmond->setShaderProgram(standardShaderProg);
    SonnensystemObjekt* phobos = new SonnensystemObjekt();
        phobos->dist = 2;
        phobos->winkelSpeedSelf = 8;
        phobos->winkelSpeedParent = 8;
        //phobos->loadVertices();
        //phobos->loadModel(QString("H:/CG/qtp2/models/phobos.obj.bin"), false);
        phobos->copyBuffer(this);
        phobos->loadTexture(QString(":/textures/phobosbump.jpg"));
        phobos->setShaderProgram(standardShaderProg);
    SonnensystemObjekt* deimos = new SonnensystemObjekt();
        deimos->dist = 2;
        deimos->winkelSpeedSelf = 4;
        deimos->winkelSpeedParent = 4;
        //deimos->loadVertices();
        //deimos->loadModel(QString("H:/CG/qtp2/models/deimos.obj.bin"), false);
        deimos->copyBuffer(this);
        deimos->loadTexture(QString(":/textures/deimosbump.jpg"));
        deimos->setShaderProgram(standardShaderProg);

    erde->children->push_back(erdmond);
    mars->children->push_back(phobos);
    mars->children->push_back(deimos);
    this->children->push_back(merkur);
    this->children->push_back(venus);
    this->children->push_back(erde);
    this->children->push_back(mars);
    this->children->push_back(jupiter);
    this->children->push_back(saturn);
    this->children->push_back(uranus);
    this->children->push_back(neptun);

}

void SonnensystemObjekt::setShaderProgram(QOpenGLShaderProgram* myshader){
    this->shaderProgram = myshader;
}

void SonnensystemObjekt::render(QMatrix4x4 parentMatrix, myCam* cam, int time)
{
    this->timer++;
    this->winkelSelf  = (this->winkelSpeedSelf * time );
    this->winkelParent = (this->winkelSpeedParent * time );

    this->matrix.setToIdentity();
    this->matrix.rotate(this->winkelParent, 0.0, 1.0, 0.0);
    this->matrix.translate(this->dist, 0.0 ,0.0);
    this->matrix.rotate(this->winkelSelf, 0.0, 1.0, 0.0);
    this->matrix = parentMatrix * this->matrix;
    this->invtransmatrix = this->matrix.inverted().transposed();
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
    int unifitMatrix = shaderProgram->uniformLocation("invtransmatrix");

    int unifMatrixProjection = shaderProgram->uniformLocation("projmatrix");
    int unifMatrixView = shaderProgram->uniformLocation("viewmatrix");
    int uniftimer = shaderProgram->uniformLocation("timer");

    if(this->isSun)
    {
        //QOpenGLFunctions::glActiveTexture(GL_TEXTURE0);

        qTexWave->bind(0);
            shaderProgram->setUniformValue("textureWave",0);
                 //glGetUniformLocation(shaderProgram->programId(), "textureWave");
       //int t2 = shaderProgram->setUniformValue(tex2, tex2);
    }
    shaderProgram->setUniformValue(unifMatrix,this->matrix);
    shaderProgram->setUniformValue(unifitMatrix, this->invtransmatrix);
    shaderProgram->setUniformValue(unifMatrixProjection, cam->projMatrix);
    shaderProgram->setUniformValue(unifMatrixView, cam->viewMatrix);
    shaderProgram->setUniformValue(uniftimer,this->timer);

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

    if(this->isSun)
        qTexWave->release();
    qTex->release();
    ibo->release();
    vbo->release();
    for (uint i = 0; i<this->children->size(); i++){
        this->children->at(i)->render(this->matrix, cam, time);
    }
}

SonnensystemObjekt::SonnensystemObjekt()
{
    this->vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    this->ibo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

    this->isSun = false;
    this->dist =0;
    this->winkelParent = 0;
    this->winkelSelf = 0;
    this->winkelSpeedParent = 0;
    this->winkelSpeedSelf =0;
    this->usesNormals = false;
    this->matrix.setToIdentity();
    this->children = new std::vector<SonnensystemObjekt*>();
    this->timer = 0;
    this->matrix.setToIdentity();

}

SonnensystemObjekt::~SonnensystemObjekt()
{
    delete this->ibo;
    delete this->vbo;
    delete this->qTex;
}

float myMod(float f, int i)
{
    return (f-(int)f)+((int)f%i);
}


