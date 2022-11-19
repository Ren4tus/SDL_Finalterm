#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MapManager.h"
#include "GameData.h"
const std::string PlayState::s_menuID = "PLAY";
void PlayState::update()
{
	GameState::update();
	MapManager::Instance()->update();
}

void PlayState::render()
{
	//���� �� ������ ��� ȭ���� ��Ӱ� �ϱ�
	TheTextureManager::Instance()->drawRect(0, 0, Game::Instance()->getWindowWidth(), Game::Instance()->getWindowHeight(),
		TheGame::Instance()->getRenderer(), 0, 0, 0, 180, true);
	GameState::render();
	//�� ���� ������ �׸�
	MapManager::Instance()->drawMap();

}

bool PlayState::onEnter()
{
	//�̹��� �ε�
	loadImage("Assets/UI/bg/play_BG.jpg", "playBG");
	loadImage("Assets/UI/mapBG.png", "MapBG");
	loadImage("Assets/UI/Node.png", "Node");
	loadImage("Assets/UI/marker.png", "Marker");

	//���� �ε�
	TheMusicManager::Instance()->loadAudio("Assets/Audio/playStateBGM.mp3", "playStateBGM", true);
	//������� ����
	TheMusicManager::Instance()->controlMusic(PLAY);
	if (!GameState::onEnter()) {
		return false;
	}
	m_gameObjects.push_back(new SDLGameObject(new LoaderParams(0, 0, TheGame::Instance()->getWindowWidth(), TheGame::Instance()->getWindowHeight(), "playBG")));
	m_gameObjects.push_back(new SDLGameObject(new LoaderParams(50, 0, 1300, 900, "MapBG")));



	//���� ����ִ� ��� �� ����
	if(MapManager::Instance()->isEmpty())
		MapManager::Instance()->createNewMap();
	std::cout << "entering PlayState\n";
	return true;
}


bool PlayState::onExit()
{
	GameState::onExit();

	TheTextureManager::Instance()->clearFromTextureMap("playBG");
	TheTextureManager::Instance()->clearFromTextureMap("MapBG");
	TheTextureManager::Instance()->clearFromTextureMap("Node");
	TheTextureManager::Instance()->clearFromTextureMap("Marker");

	std::cout << "exiting PlayState\n";
	return true;
}
