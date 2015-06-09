#include "game.h"

Game::Game(){
    myScene = new GameScene();
    myScene.initScene();
	cam = new myCam();
	cam->aktivatePlaymode(QVector3D(this->myScene.secondaryObjects->at(0)->worldMatrix.column(3).x(),this->myScene.secondaryObjects->at(0)->worldMatrix.column(3).y(),this->myScene.secondaryObjects->at(0)->worldMatrix.column(3).z()));

}

void Game::gameStep(){
	
	this->myScene.render(cam);
	
	if (this->cam->isMoving)
		this->cam->moveStep();
	else if (this->finish)
		;
	// test auf spielende
	else if (!this->blackBall.isActive && this->watch && !this->myScene.hasActives()) {
		this->finish = true;
		if (!this->turn) //p1 turn
			if 
		else			 //p2 turn
	}
}
//void Game::turn(int player, bool &finish, bool &win)
//{
//
//}
