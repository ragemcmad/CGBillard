#ifndef THEGAME
#define THEGAME
#include "GameScene.h"
#include "cam.h"
#include "kugel.h"
class Game {
public:
	
	int gameState;
	
	bool turn; // false = p1 | true = p2
    bool watch; // false = play | true = watch
	bool finish = false;
	
	bool setBall = false;
	
	bool teamAreSet = false;
	bool p1HasFull; // true = p1 full | false = p1 half
	
	GameScene* myScene;
	myCam* cam;
	
    Kugel* blackBall;
    Kugel* whiteBall;
    GameObject* koe;
	
    Game();
	void resetGame();
	void gameStep();
    void shoot(int power);
    void camMove(int x, int y);
    void camRotate(int x, int y);
    void updateKoe();

private:
    //void turn(int player, bool &finish,bool &win);
	
};
#endif THEGAME
