#include "GameEndState.h"
#include "MenuState.h"
#include "PlayState.h"
#include "GameStateMachine.h"
#include "GameData.h"
#include "MapManager.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "Game.h"
bool GameEndState::onEnter()
{
	loadImage("Assets/main.png", "mainbutton");
	loadImage("Assets/restart.png", "restartbutton");
	if (!GameState::onEnter()) { return false; }
	int w, h;
	TheTextureManager::Instance()->imageQuerySize("gameovertext", &w, &h);
	m_gameObjects.push_back(new SDLGameObject(new LoaderParams(TheGame::Instance()->getWindowWidth() / 2 - w / 2, 50, w, h, "gameovertext")));
	m_gameObjects.push_back(new MenuButton(new LoaderParams(TheGame::Instance()->getWindowWidth() / 2 - 100, h + 100, 200, 80, "mainbutton"), s_gameOverToMain));
	m_gameObjects.push_back(new MenuButton(new LoaderParams(TheGame::Instance()->getWindowWidth() / 2 - 100, h + 200, 200, 80, "restartbutton"), s_restartPlay));
	return true;
}
bool GameEndState::onExit()
{
	GameState::onExit();

	TheTextureManager::Instance()->clearFromTextureMap("gameovertext");
	TheTextureManager::Instance()->clearFromTextureMap("mainbutton");
	TheTextureManager::Instance()->clearFromTextureMap("restartbutton");

	std::cout << "exiting GameEndState \n";
	return true;
}
void GameEndState::s_gameOverToMain()
{
	TheGameStateMachine::Instance()->changeState(new MenuState());
}

void GameEndState::s_restartPlay()
{
	//맵, 게임 데이터 초기화
	GameData::Instance()->initGameData();
	MapManager::Instance()->clean();
	TheGameStateMachine::Instance()->changeState(new PlayState());
}
