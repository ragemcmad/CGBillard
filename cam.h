#ifndef CAM
#define CAM


#include<QOpenGLShaderProgram>
#include<QOpenGLBuffer>
#include"animation.h"

class myCam {
private:
    bool activePlaymode;
    bool freeCameramode;
    QVector3D kugelWhite;
    float angleX;
    float angleY;
    float distanz;
	
    QVector3D moveZiel;
    QVector3D moveLookatZiel;
	
    QVector3D moveStart;
    QVector3D moveLookatStart;
	
public:
    float moveDuration; // max Zeit/Framezahl
    float moveTime; // vergangene Zeit/Framezahl

    QMatrix4x4 viewMatrix,projMatrix;
    std::vector<Animation> animations;
    QMatrix4x4 viewMatrixCube[6];
    bool isCubeCamera;

    myCam(float fov = 95.0f, float aspect = 1201.0f/771.0f);
    bool isMoving;

    QVector3D getPositionFromViewMatrix(QMatrix4x4 matrix);
    void queueAnimation(QVector3D ziel, QVector3D zielLookAt, int duration = 500);
	void nextAnimation();
    void moveStep(int time);
    void aktivatePlaymode(QVector3D kugelWhite, int abstand = 30);
    void aktivateWatchmode();
    void camRotate(int x,int y);
    void camMove(int x, int y);  
    float getCamAngle();
};


#endif // CAM

