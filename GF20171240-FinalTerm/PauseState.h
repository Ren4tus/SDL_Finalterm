#pragma once
#include "GameState.h"
class PauseState : public GameState {
public:
	PauseState() {};
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_pauseID; }

private:
	static const std::string s_pauseID;
	static void s_resumePlay();
	static void s_pauseToMain();
};