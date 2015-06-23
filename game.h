#ifndef THEGAME
#define THEGAME
#include "GameScene.h"
#include "cam.h"
#include "kugel.h"
#include <windows.h>
#include <mmsystem.h>
#include "soundsys.h"

class Game {
public:
    bool turn; // false = p1 | true = p2
    bool watch; // false = play | true = watch
    bool finish;
    bool setBall;
    bool teamsAreSet;
	bool p1HasFull; // true = p1 full | false = p1 half
    bool hatEingelocht;
    bool hatGegnerEingelocht;
    bool killMe;

	GameScene* myScene;
	myCam* cam;
	
    Kugel* blackBall;
    Kugel* whiteBall;
    GameObject* koe;
	
    Game();
    ~Game();
	void resetGame();
	void cancel();
    void setWinner();
    void moveStuff(float i);
    void renderStuff();
    void prepareLogic();
	void gameStep();
    void shoot();
    void camMove(int x, int y);
    void camRotate(int x, int y);
    void ballMove(int x, int y);
    void startTurn();
    void updateKoe();
    void animateLights();
    void resetWhiteBall();
};
#endif
