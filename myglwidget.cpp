
#include "myglwidget.h"


#include <QKeyEvent>
#include <QWheelEvent>
#include <QOpenGLBuffer>
#include <qdebug.h>
#include <iostream>


MyGLWidget::MyGLWidget(QWidget *parent) : QGLWidget(parent)
{
    this->isPressed = false;
    this->timer = new QTimer(parent);
    QObject::connect(this->timer,SIGNAL(timeout()),this,SLOT(update()));
    //QObject::connect(parent->parent()->children().at,SIGNAL(actionStandard_Game()),SLOT(newGame()));
    timer->start(25);
}



MyGLWidget::~MyGLWidget()
{
    delete this->timer;
    //delete this->sso;

}

void MyGLWidget::update()
{
    //receiveRotationZ(counter);
    counter++;
    updateGL();
}

void MyGLWidget::wheelEvent(QWheelEvent *event)
{
//    if (event->delta()>0){
//        this->cam->zoomIn();
//    } else {
//        this->cam->zoomOut();
//    }
qDebug() << "scroll " <<event->delta();
}

void MyGLWidget::mousePressEvent(QMouseEvent *e){
    this->isPressed = true;
    this->mousepositionOldX = e->x();
    this->mousepositionOldY = e->y();

}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e){
    if ((this->isPressed)){// && (this->theGame->show)){
        this->theGame->camRotate(mousepositionOldX-e->x(),mousepositionOldY-e->y());
    }

    this->mousepositionOldX = e->x();
    this->mousepositionOldY = e->y();

}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *e){
    this->isPressed = false;
}

void MyGLWidget::keyPressEvent(QKeyEvent * event)
{

    if(event->key() == Qt::Key_A)
    {
        this->theGame->camMove(1,0);
        this->theGame->ballMove(-1,0);
    }
    if(event->key() == Qt::Key_W)
    {
        this->theGame->camMove(0,1);
        this->theGame->ballMove(0,-1);
    }
    if(event->key() == Qt::Key_S)
    {
        this->theGame->camMove(0,-1);
        this->theGame->ballMove(0,1);
    }
    if(event->key() == Qt::Key_D)
    {
        this->theGame->camMove(-1,0);
        this->theGame->ballMove(1,0);
    }
    if(event->key() == Qt::Key_Space)
        this->theGame->shoot();
	if(event->key() == Qt::Key_Enter)
        this->theGame->animateLights();
	if(event->key() == Qt::Key_Escape)
		this->theGame->cancel();
    if(event->key() == Qt::Key_Plus)
        this->theGame->myScene->lights->adjustIntensity(1);
    if(event->key() == Qt::Key_Minus)
        this->theGame->myScene->lights->adjustIntensity(-1);
    else
        QGLWidget::keyPressEvent(event);
    updateGL();

}

void MyGLWidget::newGame()
{
    this->theGame->resetGame();
}

void MyGLWidget::newTraining1()
{
    this->theGame->loadTraining();
}

void MyGLWidget::newShow()
{
    this->theGame->loadShow();
}
void MyGLWidget::paintGL()
{
    // Clear buffer to set color and alpha
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Apply model view transformations
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //glTranslatef(this->distanceX, this->distanceY, this->distanceZ);
    //glRotatef(this->rotationZ,0,1,1);

    //QMatrix4x4 m;
    //m.setToIdentity();
    //this->sso->render(m, cam, counter);

    this->theGame->gameStep();
}

void MyGLWidget::resizeGL(int width, int height)
{
   // Compute aspect ratio
   height = (height == 0) ? 1 : height;
   //GLfloat aspect = (GLfloat)width / (GLfloat)height;

   // Set viewport to cover the whole window
   glViewport(0, 0, width, height);

   // Set projection matrix to a perspective projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-0.05 , 0.05, -0.05, 0.05, 0.1, 1000.0);
   //gluPerspective(45.0f, aspect, 0.1, 100.0);
}

void MyGLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


    glClearDepth(1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    this->counter = 0;
    this->theGame = new Game();

    if (glewInit() != GLEW_OK)
        std::cout<< "glew error\n"<<std::endl;

}
