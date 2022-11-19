#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "SDL.h"
#include <SDL_ttf.h>
#include "GameObject.h"
#include "SDLGameObject.h"
#include "Player.h"
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "InputHandler.h"
#include "GameStateMachine.h"
class GameStateMachine;

class Game {
public:

	~Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void render();
	void update();
	bool running() { return m_bRunning; }
	void handleEvents();
	void clean();
	static Game* Instance() {
		if (s_pInstance == NULL) {
			s_pInstance = new Game();
		}
		return s_pInstance;
	}
	SDL_Renderer* getRenderer() const { return m_pRenderer; }

	void quit() {
		m_bRunning = false;
	}
	
	/// <summary>
	/// 윈도우 크기 설정
	/// </summary>
	/// <param name="width"> 윈도우 가로 </param>
	/// <param name="height"> 윈도우 세로 </param>
	void setWindowScreen(int width, int height);
	int getWindowWidth();
	int getWindowHeight();

private:
	Game();
	static Game* s_pInstance;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;
	//int m_currentFrame;
	//std::vector<GameObject*> m_gameObjects;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	//GameStateMachine* m_pGameStateMachine;
};
typedef Game TheGame;