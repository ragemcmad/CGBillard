#ifndef THEGAME
#define THEGAME
#include "GameScene.h"
#include "cam.h"
class Game {
public:
	
	int gameState;
	
	bool turn; // false = p1 | true = p2
	bool watch; // false = watch | true = play;
	bool finish = false;
	
	bool p1HasTeam = false;
	bool p2HasTeam = false;
	bool p1HasFull; // true = p1 full | false = p1 half
	bool p2HasFull;
	
	GameScene* myScene;
	myCam* cam;
	
	GameObject* blackBall;
	GameObject* whiteBall;
	
    Game(GameScene gameScene);
	void gameStep();
	
	
private:
    //void turn(int player, bool &finish,bool &win);
	
};
#endif THEGAME
