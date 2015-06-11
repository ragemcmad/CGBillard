#ifndef CAM
#define CAM



#include<QOpenGLShaderProgram>
#include<QOpenGLBuffer>

class myCam {
private:
    bool activePlaymode;
    bool freeCameramode;
    QVector3D kugelWhite;
    float angleX;
    float angleY;
    float distanz;

public:
    QMatrix4x4 viewMatrix,projMatrix;
    myCam();

    void aktivatePlaymode(QVector3D kugelWhite);
    void aktivateWatchmode();
    void camRotate(int x,int y);
    void camMove(int x, int y);  
    float getCamAngle();
};


#endif // CAM

