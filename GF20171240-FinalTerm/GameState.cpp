#include "GameState.h"
#include "GameObject.h"
#include <vector>
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include <vector>
GameState::GameState()
{
}
void GameState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->update();

		//���� �����̶�� update ȣ���� �׸��д�
		if (toBeExecuted) {
			return;
		}
	}
}

void GameState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}

}

bool GameState::onEnter()
{
	for (int i = 0; i < fileNames.size(); i++) {
		if (!TheTextureManager::Instance()->load(fileNames[i][0], fileNames[i][1], TheGame::Instance()->getRenderer())) {
			std::cout << "ImageLoad Failed - Error Name: " + fileNames[i][1] << std::endl;
			return false;
		}
	}
	return true;
}

bool GameState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->clean();
		delete m_gameObjects[i];
	}
	m_gameObjects.clear();
	//������� ����
	TheMusicManager::Instance()->controlMusic(HALT);
	TheMusicManager::Instance()->clearMusic();

	//�ٷ� �������� �ʰ� ���� ���� ���·� �����
	execute();
	return true;
}

void GameState::loadImage(std::string fileName, std::string name)
{
	std::vector<std::string> temp;
	fileNames.push_back(temp);
	fileNames.back().push_back(fileName);
	fileNames.back().push_back(name);
}

