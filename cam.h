#ifndef CAM
#define CAM



#include<QOpenGLShaderProgram>
#include<QOpenGLBuffer>

class myCam {
public:
    QMatrix4x4 viewMatrix,projMatrix;
    int xwinkel, ywinkel;
    float dist;
    float x,y,z;
    int step;
    const float minDist = 1;
    myCam();


    void camRotate(int x,int y);
    void camMove(int x, int y);


    void camUp();
    void camDown();
    void camLeft();
    void camRight();

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void moveFront();
    void moveBack();
    void resetView();

    void zoomIn();
    void zoomOut();
    void updateView();
};


#endif // CAM

