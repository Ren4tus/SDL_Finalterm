#include <SDL.h>
#include "Game.h"
Game* g_game = 0;



int main(int argc, char* args[])
{
	if (TheGame::Instance()->init("GF_FinalTerm", 100, 100, 1440, 900, false)) {

		while (TheGame::Instance()->running()) {
			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();
		}
	}
	else {
		std::cout << "game init failure " << SDL_GetError() << "\n";
		return -1;
	}

	TheGame::Instance()->clean();
	return 0;
}