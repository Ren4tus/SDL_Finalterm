#include "MenuButton.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Game.h"
MenuButton::MenuButton(const LoaderParams* pParams, void(*callback)())
	: SDLGameObject(pParams),
	m_callback(callback)
{
}

void MenuButton::draw()
{
	if (m_currentFrame == CLICKED) {
		TextureManager::Instance()->drawEx(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height,
			TheGame::Instance()->getRenderer(), m_destW, m_destH);
	}
	else if (m_currentFrame == MOUSE_OVER) {
		TextureManager::Instance()->drawEx(m_textureID, (int)m_position.getX() + 5, (int)m_position.getY() + 5, m_width, m_height,
			TheGame::Instance()->getRenderer(), m_destW, m_destH);
	}
	else if (m_currentFrame == MOUSE_OUT) {
		TextureManager::Instance()->drawEx(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height,
			TheGame::Instance()->getRenderer(), m_destW, m_destH);
	}
}

void MenuButton::update()
{
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();
	if (pMousePos->getX() < (m_position.getX() + m_destW)
		&& pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_destH)
		&& pMousePos->getY() > m_position.getY()) {

		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased) {
			m_currentFrame = CLICKED;
			m_callback();
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

void MenuButton::clean()
{
	SDLGameObject::clean();
}
