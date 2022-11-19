#pragma once
#include "GameState.h"

class GameEndState abstract : public GameState  {
public:
	virtual bool onEnter();
	virtual bool onExit();
protected:
	static void s_gameOverToMain();
	static void s_restartPlay();
};