#include "Game.h"
#include "TextureManager.h"
#include "PlayState.h"
#include "MenuState.h"
#include "GameStateMachine.h"
#include <SDL_mixer.h>
Game* Game::s_pInstance = 0;
void Game::setWindowScreen(int width, int height)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
}
int Game::getWindowWidth()
{
	return SCREEN_WIDTH;
}
int Game::getWindowHeight()
{
	return SCREEN_HEIGHT;
}
Game::Game() {
	m_bRunning = false; m_pWindow = NULL; m_pRenderer = NULL;
	SCREEN_WIDTH = NULL;
	SCREEN_HEIGHT = NULL;

}
Game::~Game() {

}
bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		int flags = 0;

		if (fullscreen)
			flags = SDL_WINDOW_FULLSCREEN;
		else
			flags = SDL_WINDOW_SHOWN;

		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		//아이콘 설정
		SDL_Surface* icon = IMG_Load("Assets/UI/Node.png");
		SDL_SetWindowIcon(m_pWindow, icon);
		SDL_FreeSurface(icon);
		//스크린 크기 저장
		setWindowScreen(width, height);
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) {
				SDL_SetRenderDrawColor(
					m_pRenderer,
					255, 0, 0, 255);
			}
			else {
				return false; //렌더러 생성 실패
			}

			//TTF Init은 SDL_INIT_EVERYTHING에 포함되지 않으므로 따로 초기화해준다
			if (TTF_Init() == -1) {
				std::cout << "SDL_ttf could not initialize! SDL_ttf ERROR: " << TTF_GetError << std::endl;
			}
			//SDL_Mixer 초기화
			if (SDL_Init(SDL_INIT_AUDIO) < 0) {
				std::cout<<("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			}
			if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048) < 0) {
				std::cout << ("SDL_mixer could not initialize!", SDL_GetError());
			}
			TheTextureManager::Instance()->setFont("Assets/NanumSquareRoundL.ttf", 28);


		}
		else {
			return false; //윈도우 생성 실패
		}
	}
	else {
		return false; //SDL 초기화 실패
	}

	TheGameStateMachine::Instance()->changeState(new MenuState());

	m_bRunning = true;
	return true;
}

void Game::handleEvents() {

	TheInputHandler::Instance()->update();
	if (TheInputHandler::Instance()->isKeyOneDown(SDL_SCANCODE_UP)) {
		TheMusicManager::Instance()->changeVolume(5);
	}
	else if (TheInputHandler::Instance()->isKeyOneDown(SDL_SCANCODE_DOWN)) {
		TheMusicManager::Instance()->changeVolume(-5);
	}
}
void Game::clean()
{
	InputHandler::Instance()->clean();
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	//sdl mixer 종료
	Mix_Quit();
	//sdl image 종료
	IMG_Quit();
	//sdl 종료
	SDL_Quit();
}
void Game::update()
{
	TheGameStateMachine::Instance()->update();
	TheGameStateMachine::Instance()->clean();
}

void Game::render()
{

	SDL_RenderClear(m_pRenderer);
	TheGameStateMachine::Instance()->render();
	SDL_RenderPresent(m_pRenderer);
}
