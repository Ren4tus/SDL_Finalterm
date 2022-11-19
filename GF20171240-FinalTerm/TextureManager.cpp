#include "TextureManager.h"
#include "Game.h"
#include <SDL_ttf.h>
#include <string>
#include "han2unicode.h"
TextureManager* TextureManager::s_pInstance = 0;
void TextureManager::setFont(const char* root, int size)
{
	mFont = TTF_OpenFont(root, size);
}

void TextureManager::drawText(std::string text, int x, int y, SDL_Renderer* pRenderer, Uint8 r,Uint8 g,Uint8 b, Uint8 a)
{
	TTF_Init();
	SDL_Color textColor = { r, g, b, a };
	SDL_Texture* mTexture = NULL;
	unsigned short unicode[128];
	const char* transText = text.c_str();
	han2unicode(transText, unicode);
	SDL_Surface* textSurface = TTF_RenderUNICODE_Blended(mFont, unicode, textColor);

	mTexture = SDL_CreateTextureFromSurface(pRenderer, textSurface);
	SDL_FreeSurface(textSurface);
	
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_QueryTexture(mTexture, NULL, NULL, &srcRect.w, &srcRect.h);
	srcRect.x = 0;
	srcRect.y = 0;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopy(pRenderer, mTexture, &srcRect, &destRect);

	SDL_DestroyTexture(mTexture);
}

void TextureManager::clearFromTextureMap(std::string id)
{
	SDL_DestroyTexture(m_textureMap[id]);
	m_textureMap.erase(id);
}


TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
}
bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer) {
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
	if (pTempSurface == 0) {
		return false;
	}
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);

	if (pTexture != 0) {
		m_textureMap[id] = pTexture;
		return true;
	}
	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}
void TextureManager::drawEx(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, int destW, int destH, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = width;
	srcRect.h = height;
	destRect.w = destW;
	destRect.h = destH;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}


void TextureManager::drawRect(int x, int y, int width, int height, SDL_Renderer* pRenderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool Fill)
{
	SDL_Rect rect = { x,y,width,height };
	SDL_SetRenderDrawColor(pRenderer, r, g, b, a);
	SDL_SetRenderDrawBlendMode(TheGame::Instance()->getRenderer(), SDL_BLENDMODE_BLEND);
	if (Fill)
		SDL_RenderFillRect(pRenderer, &rect);
	else
		SDL_RenderDrawRect(pRenderer, &rect);
	SDL_SetRenderDrawBlendMode(TheGame::Instance()->getRenderer(), SDL_BLENDMODE_NONE);
}

void TextureManager::imageQuerySize(std::string id, int* w, int* h)
{
	SDL_QueryTexture(m_textureMap[id], NULL, NULL, w, h);
}
