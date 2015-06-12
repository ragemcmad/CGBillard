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

	QVector3D* moveZiel;
	QVector3D* moveLookatZiel;
	
	QVector3D* moveStart;
	QVector3D* moveLookatStart;
	
	int moveDuration; // max Zeit/Framezahl
	int moveTime; // vergangene Zeit/Framezahl
	
public:
    QMatrix4x4 viewMatrix,projMatrix;
    myCam();
    bool isMoving;

	void startAnimation(QVector3D* start, Qvector3D* startLookAt, int duration = 500);
    void moveStep();
    void aktivatePlaymode(QVector3D kugelWhite);
    void aktivateWatchmode();
    void camRotate(int x,int y);
    void camMove(int x, int y);  
    float getCamAngle();
};


#endif // CAM

