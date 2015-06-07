#ifndef MYQGLWIDGET_H
#define MYQGLWIDGET_H

#include <QWidget>
#include <QGLWidget>

class MyQGLWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyQGLWidget(QWidget *parent = 0);
    MyQGLWidget();
    ~MyQGLWidget();



};



#endif // MYQGLWIDGET_H
