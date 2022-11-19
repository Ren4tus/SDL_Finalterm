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

		//������ ����
		SDL_Surface* icon = IMG_Load("Assets/UI/Node.png");
		SDL_SetWindowIcon(m_pWindow, icon);
		SDL_FreeSurface(icon);
		//��ũ�� ũ�� ����
		setWindowScreen(width, height);
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) {
				SDL_SetRenderDrawColor(
					m_pRenderer,
					255, 0, 0, 255);
			}
			else {
				return false; //������ ���� ����
			}

			//TTF Init�� SDL_INIT_EVERYTHING�� ���Ե��� �����Ƿ� ���� �ʱ�ȭ���ش�
			if (TTF_Init() == -1) {
				std::cout << "SDL_ttf could not initialize! SDL_ttf ERROR: " << TTF_GetError << std::endl;
			}
			//SDL_Mixer �ʱ�ȭ
			if (SDL_Init(SDL_INIT_AUDIO) < 0) {
				std::cout<<("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			}
			if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048) < 0) {
				std::cout << ("SDL_mixer could not initialize!", SDL_GetError());
			}
			TheTextureManager::Instance()->setFont("Assets/NanumSquareRoundL.ttf", 28);


		}
		else {
			return false; //������ ���� ����
		}
	}
	else {
		return false; //SDL �ʱ�ȭ ����
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
	//sdl mixer ����
	Mix_Quit();
	//sdl image ����
	IMG_Quit();
	//sdl ����
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
