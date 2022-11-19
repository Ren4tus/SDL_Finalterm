#include "GameStateMachine.h"
#include "IngameState.h"
#include "TextureManager.h"
#include "Game.h"
std::vector<GameState*> GameStateMachine::m_gameStates;
GameStateMachine* GameStateMachine::s_pInstance = NULL;
void GameStateMachine::pushState(GameState* pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState* pState)
{
	if (!m_gameStates.empty()) {
		if (m_gameStates.back()->getStateID() == pState->getStateID()) {
			return;

		}
		//pState�� gameoverState��� ��� state�� pop�Ѵ�.
		else if (pState->getStateID() == "GAMEOVER") {
			for (int i = 0; i < m_gameStates.size(); i++) {
				m_gameStates[i]->onExit();
			}
		}
		else {
			m_gameStates.back()->onExit();	
		}

	}

	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
	if (!m_gameStates.empty()) {
		for (int i = 0; i < m_gameStates.size(); i++) {
			if (!m_gameStates[m_gameStates.size() -i - 1]->getExecute()) {
				m_gameStates[m_gameStates.size() - i - 1]->onExit();
				return;
			}

		}
	}
}

void GameStateMachine::update()
{
	if (!m_gameStates.empty()) {
		m_gameStates.back()->update();
	}

}

void GameStateMachine::render()
{
	if (!m_gameStates.empty()) {
		//���� ������ ��� ���� ������ ������Ʈ���� �׸���
		if (m_gameStates.back()->getStateID() == "PAUSE") {
			m_gameStates.at(m_gameStates.size() - 2)->render();
			TheTextureManager::Instance()->drawRect(0, 0, TheGame::Instance()->getWindowWidth(), TheGame::Instance()->getWindowHeight(), TheGame::Instance()->getRenderer(), 0, 0, 0, 180,true);
		}
		m_gameStates.back()->render();
	}
}

void GameStateMachine::clean()
{

	//���� ������ state���� ���� �����Ѵ�
	std::vector<GameState*>::iterator iterPos = m_gameStates.begin();
	while (iterPos != m_gameStates.end()) {
		if (m_gameStates.at(std::distance(m_gameStates.begin(), iterPos))->getExecute()) {
			delete m_gameStates.at(std::distance(m_gameStates.begin(), iterPos));
			iterPos = m_gameStates.erase(iterPos);
			continue;
		}
		++iterPos;
	}
}
