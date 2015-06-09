#include "game.h"

Game::Game(GameScene scene){
    myScene = scene;
    myScene.initScene();

}

void Game::gameStep(){
}
//void Game::turn(int player, bool &finish, bool &win)
//{
//
//}
