#pragma once
#include "GameState.h"
#include <vector>

class GameStateMachine {
public:
	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();
	void update();
	void render();
	void clean();
	std::vector <GameState*> getGameState() { return m_gameStates; }
	static GameStateMachine* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new GameStateMachine();

		}
		return s_pInstance;
	}
private:
	GameStateMachine() {}
	static GameStateMachine* s_pInstance;
	static std::vector<GameState*> m_gameStates;

};

typedef GameStateMachine TheGameStateMachine;