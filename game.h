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
	
	bool p1HasTeam = false;
	bool p2HasTeam = false;
	bool p1HasFull; // true = p1 full | false = p1 half
	bool p2HasFull;
	
	GameScene* myScene;
	myCam* cam;
	
    Kugel* blackBall;
    Kugel* whiteBall;
    GameObject* koe;
	
    Game();
	void gameStep();
    void shoot();
    void camMove(int x, int y);
    void camRotate(int x, int y);


private:
    //void turn(int player, bool &finish,bool &win);
	
};
#endif THEGAME
