#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <GL/glew.h>
#include <QGLWidget>
#include <qtimer.h>
#include <QOpenGLBuffer>

#include "cam.h"
#include "gamescene.h"
#include "game.h"

class MyGLWidget : public QGLWidget
{
    Q_OBJECT


private:
    QTimer *timer;
    int counter;
    //void loadModels();
    //SonnensystemObjekt* sso;
    Game* theGame;
    //float rotationZ;
    //float distanceX, distanceY, distanceZ;
    //QOpenGLShaderProgram shaderProgram;
    bool isPressed;
    int mousepositionOldX;
    int mousepositionOldY;
    GameScene scene;

public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

signals:

public slots:
    void update();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent*);
    void keyPressEvent(QKeyEvent*);
    void newGame();
    void newTraining1();
    void newShow();
};

#endif // MYGLWIDGET_H
