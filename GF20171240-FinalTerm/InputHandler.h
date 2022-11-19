#pragma once
#include "SDL.h"
#include <vector>
#include <map>
#include <string>
#include "Vector2D.h"
class InputHandler
{
public:
	~InputHandler() {}
	static InputHandler* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new InputHandler();
		}
		return s_pInstance;
	}
	void update();
	void clean();
	bool isKeyDown(SDL_Scancode key);
	bool isKeyOneDown(SDL_Scancode key);
	bool getMouseButtonState(int buttonNumber)const;
	Vector2D* getMousePosition()const;
private:
	InputHandler();
	static InputHandler* s_pInstance;
	const Uint8* m_keystates;
	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;
	std::map<int, bool> pressedMap;
};

typedef InputHandler TheInputHandler;
enum mouse_buttons {
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};