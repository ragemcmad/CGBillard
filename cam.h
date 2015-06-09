#ifndef CAM
#define CAM



#include<QOpenGLShaderProgram>
#include<QOpenGLBuffer>

class myCam {
private:
    bool activePlaymode;
    bool freeCameramode;
    QVector3D kugelWhite;

public:
    QMatrix4x4 viewMatrix,projMatrix;
    myCam();

    void aktivatePlaymode(QVector3D kugelWhite);
    void camRotate(int x,int y);
    void camMove(int x, int y);  
};


#endif // CAM

