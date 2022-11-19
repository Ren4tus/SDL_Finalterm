#include "GameOverState.h"
#include "Game.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "GameData.h"
#include "MapManager.h"
const std::string GameOverState::s_gameOverID = "GAMEOVER";
GameOverState::GameOverState()
{


}


bool GameOverState::onEnter()
{
	loadImage("Assets/gameover.png", "gameovertext");
	GameEndState::onEnter();

	std::cout << "entering GameOverState \n";
	return true;
}
