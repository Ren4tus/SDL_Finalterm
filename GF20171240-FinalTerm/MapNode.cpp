#include "MapNode.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "MapManager.h"
void MapNode::draw()
{
	SDLGameObject::draw();

	if (m_currentFrame == MOUSE_OVER) {
		TheTextureManager::Instance()->drawEx("Marker",
			m_position.getX() - (markerSize / 2 - m_destW / 2),
			m_position.getY() - (markerSize / 2 - m_destH / 2),
			realMarkerSize, realMarkerSize, TheGame::Instance()->getRenderer(), markerSize, markerSize);
	}
}

void MapNode::update()
{
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();
	if (pMousePos->getX() < (m_position.getX() + m_destW)
		&& pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_destH)
		&& pMousePos->getY() > m_position.getY()) {

		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased) {
			m_currentFrame = CLICKED;
			//클릭된 경우 이 노드의 정보를 MapManager로 보낸다
			MapManager::Instance()->nodeClickFeedback(this);
			//노드에 등록된 함수 실행
			m_nodeCallback(type);
			m_bReleased = false;
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT)) {
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else {
		m_currentFrame = MOUSE_OUT;
	}
}

void MapNode::drawLine()
{
	for (int i = 0; i < linkedNode.size(); i++) {
		SDL_SetRenderDrawColor(TheGame::Instance()->getRenderer(), 255, 255, 255, 255);

		SDL_RenderDrawLine(TheGame::Instance()->getRenderer(),
			m_position.getX() + getDestW() / 2,
			m_position.getY() + getDestH() / 2,
			linkedNode[i]->getPosition().getX() + linkedNode[i]->getDestW() / 2,
			linkedNode[i]->getPosition().getY() + linkedNode[i]->getDestH() / 2);
	}
}

void MapNode::drawIndicater()
{
	if (type == END) {
		TheTextureManager::Instance()->drawText("End", m_position.getX() + 30, m_position.getY() - 30, TheGame::Instance()->getRenderer(), 76, 228, 213, 255);
	}
	else if (type == DOUBLETIME) {
		TheTextureManager::Instance()->drawText("DT", m_position.getX() + 30, m_position.getY() - 30, TheGame::Instance()->getRenderer(), 141, 146, 243, 255);
	}
	else if (type == HARDROCK) {
		TheTextureManager::Instance()->drawText("HR", m_position.getX() + 30, m_position.getY() - 30, TheGame::Instance()->getRenderer(), 201, 22, 117, 255);
	}
}
