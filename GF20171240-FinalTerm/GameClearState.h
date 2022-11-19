#pragma once
#include "GameEndState.h"

class GameClearState :public GameEndState {
public:
	GameClearState();
	virtual bool onEnter();
	virtual void render();
	virtual std::string getStateID() const { return s_gameOverID; }

private:
	static const std::string s_gameOverID;
};