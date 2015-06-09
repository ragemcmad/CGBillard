#ifndef THEGAME
#define THEGAME
#include "GameScene.h"
class Game {
public:
	
	int gameState;
	
	bool turn; // false = p1 | true = p2
	bool watch; // false = watch | true = play;
	bool finish = false;
	
	GameScene myScene;
	
	Game();
	void gameStep();
	
	
	private void turn(int player, bool &finish,bool &win);
	
}
#endif THEGAME