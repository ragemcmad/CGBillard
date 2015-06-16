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
	
    QVector3D moveZiel;
    QVector3D moveLookatZiel;
	
    QVector3D moveStart;
    QVector3D moveLookatStart;
	
    float moveDuration; // max Zeit/Framezahl
    float moveTime; // vergangene Zeit/Framezahl
public:
    QMatrix4x4 viewMatrix,projMatrix;
	Vector<Animation> animations;
    myCam();
    bool isMoving;

    QVector3D getPositionFromViewMatrix(QMatrix4x4 matrix);
    void queueAnimation(QVector3D ziel, QVector3D zielLookAt, int duration = 500);
	void nextAnimation();
    void moveStep(int time);
    void aktivatePlaymode(QVector3D kugelWhite);
    void aktivateWatchmode();
    void camRotate(int x,int y);
    void camMove(int x, int y);  
    float getCamAngle();
};

class Animation 
{
	public:
	
	QVector3D moveZiel;
    QVector3D moveLookatZiel;	
	float moveDuration;
	
    QVector3D moveStart;
    QVector3D moveLookatStart;
	
	Animation(QVector3D ziel, QVector3D zielLookAt, int duration)
}

#endif // CAM

