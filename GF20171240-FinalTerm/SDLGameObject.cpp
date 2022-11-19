#include "SDLGameObject.h"
#include "Game.h"
#include <math.h>
SDLGameObject::SDLGameObject(const LoaderParams* pParams)
	: GameObject(pParams), m_position((float)pParams->getX(), (float)pParams->getY()), m_velocity(0, 0), m_acceleration(0.0f, 0.0f)
{
	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_currentRow = 0;
	m_currentFrame = 0;
	m_destW = m_width;
	m_destH = m_height;
}

void SDLGameObject::draw()
{

	TextureManager::Instance()->drawEx(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height,
		TheGame::Instance()->getRenderer(), m_destW, m_destH);
}

void SDLGameObject::update()
{
}

void SDLGameObject::clean()
{
	TheTextureManager::Instance()->clearFromTextureMap(m_textureID);
}


void SDLGameObject::setModifier(int w, int h, int row, int frame, int numFrame)
{
	m_destW = w;
	m_destH = h;
	row != -1 ? m_currentRow = row : m_currentRow = m_currentRow;
	frame != -1 ? m_currentFrame = frame : m_currentFrame = m_currentFrame;
	m_numFrames != -1 ? m_numFrames = numFrame : m_numFrames = m_numFrames;
}
