#pragma once
#include "SDLGameObject.h"

class LoaderParams;

class MenuButton : public SDLGameObject {
public:
	MenuButton(const LoaderParams* pParams,
		void(*callback)());
	virtual void draw();
	virtual void update();
	virtual void clean();

protected:
	bool m_bReleased;
	void(*m_callback)();
};

enum button_state
{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
};