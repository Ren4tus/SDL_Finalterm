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
	/// @brief RenderCopyEx의 모든 기능을 사용하는 그리기 함수
	/// </summary>
	void drawEx(std::string id, int x, int y, int width, int height,
		SDL_Renderer* pRenderer,int destW, int destH ,SDL_RendererFlip flip = SDL_FLIP_NONE);

	/// <summary>
	/// @brief 네모를 그려주는 함수
	/// </summary>
	/// <param name="Fill"> true면 속이 칠해진 네모를 그린다 </param>
	void drawRect(int x, int y, int width, int height, SDL_Renderer* pRenderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool Fill=false);

	/// <summary>
	/// @brief 이미지 사이즈를 구해주는 함수
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
