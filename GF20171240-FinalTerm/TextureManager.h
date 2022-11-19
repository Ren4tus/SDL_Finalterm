#pragma once
#include "TextureManager.h"
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <map>

typedef class TextureManager
{
public:
	static TextureManager* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new TextureManager();
			return s_pInstance;
		}
		return s_pInstance;
	}
	
	~TextureManager();

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);
	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	/// <summary>
	/// @brief RenderCopyEx�� ��� ����� ����ϴ� �׸��� �Լ�
	/// </summary>
	void drawEx(std::string id, int x, int y, int width, int height,
		SDL_Renderer* pRenderer,int destW, int destH ,SDL_RendererFlip flip = SDL_FLIP_NONE);

	/// <summary>
	/// @brief �׸� �׷��ִ� �Լ�
	/// </summary>
	/// <param name="Fill"> true�� ���� ĥ���� �׸� �׸��� </param>
	void drawRect(int x, int y, int width, int height, SDL_Renderer* pRenderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool Fill=false);

	/// <summary>
	/// @brief �̹��� ����� �����ִ� �Լ�
	/// </summary>
	void imageQuerySize(std::string id, int* w, int* h);
	void setFont(const char* root, int size);
	void drawText(std::string text, int x, int y, SDL_Renderer* pRenderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void clearFromTextureMap(std::string id);
private:
	TextureManager();
	static TextureManager* s_pInstance;
	std::map<std::string, SDL_Texture*> m_textureMap;
	TTF_Font* mFont = NULL;
}TheTextureManager;
