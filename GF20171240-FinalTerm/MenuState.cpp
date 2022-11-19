#include "MenuState.h"
#include "Game.h"
#include "PlayState.h"
#include "GameStateMachine.h"
#include "MenuButton.h"
#include <vector>
#include "GameData.h"
#include "MapManager.h"
const std::string MenuState::s_menuID = "MENU";

bool MenuState::onEnter()
{
	//필요한 이미지 로드
	loadImage("Assets/UI/New.png", "newButton");
	loadImage("Assets/UI/Options.png", "optionsButton");
	loadImage("Assets/UI/Exit.png", "exitButton");
	loadImage("Assets/UI/bg/menu_bg.png", "menuBG");

	//실제로 이미지가 로드 되는 곳
	if (!GameState::onEnter()) {
		//예외 처리
		return false;
	}	

	//배경음악
	TheMusicManager::Instance()->loadAudio("Assets/Audio/mainBGM.mp3", "mainBGM", true);
	//배경음악 실행
	TheMusicManager::Instance()->controlMusic(PLAY);

	m_gameObjects.push_back(new SDLGameObject(new LoaderParams(0, 0, TheGame::Instance()->getWindowWidth(), TheGame::Instance()->getWindowHeight(), "menuBG")));
	m_gameObjects.push_back(new MenuButton(new LoaderParams(600, 350, 771, 161, "newButton"), s_menuToPlay));
	m_gameObjects.back()->setModifier(m_gameObjects.back()->getDestW() / 3, m_gameObjects.back()->getDestH() /3);
	m_gameObjects.push_back(new MenuButton(new LoaderParams(600, 550, 770, 161, "exitButton"), s_exitFromMenu));
	m_gameObjects.back()->setModifier(m_gameObjects.back()->getDestW() / 3, m_gameObjects.back()->getDestH() / 3);

	//게임 데이터 초기화
	GameData::Instance()->initGameData();
	MapManager::Instance()->clean();

	std::cout << "entering MenuState\n";
	return true;
}

bool MenuState::onExit()
{
	GameState::onExit();

	TheTextureManager::Instance()->clearFromTextureMap("playbutton");
	TheTextureManager::Instance()->clearFromTextureMap("exitbutton");


	std::cout << "exiting MenuState\n";
	return true;
}

void MenuState::s_menuToPlay()
{
	std::cout << "Play button clicked\n";
	TheGameStateMachine::Instance()->changeState(new PlayState());
}

void MenuState::s_exitFromMenu()
{
	std::cout << "Exit button clicked\n";
	TheGame::Instance()->quit();
}
