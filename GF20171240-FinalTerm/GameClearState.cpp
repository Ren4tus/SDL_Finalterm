#include "GameClearState.h"
#include "Game.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "MenuState.h"
#include "GameData.h"
#include "MapManager.h"
const std::string GameClearState::s_gameOverID = "GAMEOVER";
GameClearState::GameClearState()
{


}

bool GameClearState::onEnter()
{
	loadImage("Assets/victory.png", "gameovertext");
	GameEndState::onEnter();

	std::cout << "entering GameClearState \n";
	return true;
}

void GameClearState::render()
{
	GameState::render();

	TheTextureManager::Instance()->drawText("Your Score : " + std::to_string(GameData::Instance()->getScore()), 600, 550, TheGame::Instance()->getRenderer(), 255, 255, 255, 255);
}
