#pragma once
#include "GameEndState.h"

class GameOverState :public GameEndState {
public:
	GameOverState();
	virtual bool onEnter();
	virtual std::string getStateID() const { return s_gameOverID; }

private:
	static const std::string s_gameOverID;
};