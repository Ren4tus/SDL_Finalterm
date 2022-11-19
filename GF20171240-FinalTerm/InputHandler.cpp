#include "InputHandler.h"
#include "Game.h"
#include <iostream>
InputHandler* InputHandler::s_pInstance = 0;
InputHandler::InputHandler() {
    m_keystates = NULL;

    m_mousePosition = new Vector2D(0, 0);

    for (int i = 0; i < 3; i++) {
        m_mouseButtonStates.push_back(false);
    }
}
void InputHandler::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            TheGame::Instance()->quit();
        }
        else if (event.type == SDL_KEYUP) {
            m_keystates = SDL_GetKeyboardState(0);
        }
        else if (event.type == SDL_KEYDOWN) {
            m_keystates = SDL_GetKeyboardState(0);
        }

        if (event.type == SDL_MOUSEMOTION) {
            m_mousePosition->setX((float)event.motion.x);
            m_mousePosition->setY((float)event.motion.y);

        }
        else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                m_mouseButtonStates[LEFT] = true;
            }
            if (event.button.button == SDL_BUTTON_MIDDLE) {
                m_mouseButtonStates[MIDDLE] = true;
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                m_mouseButtonStates[RIGHT] = true;
            }
        }
        else if (event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                m_mouseButtonStates[LEFT] = false;
            }
            if (event.button.button == SDL_BUTTON_MIDDLE) {
                m_mouseButtonStates[MIDDLE] = false;
            }
            if (event.button.button == SDL_BUTTON_RIGHT) {
                m_mouseButtonStates[RIGHT] = false;
            }
        }
    }
}
void InputHandler::clean()
{
    delete m_mousePosition;

}
bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if (m_keystates != 0) {
        if (m_keystates[key] == 1) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}
bool InputHandler::isKeyOneDown(SDL_Scancode key)
{
    if (m_keystates != 0) {
        if (m_keystates[key] == 1) {
            if (pressedMap[key] == false) {
                pressedMap[key] = true;
                return true;
            }
            else {
                return false;
            }
        }
        else {
            pressedMap[key] = false;
            return false;
        }
    }
    return false;
}
bool InputHandler::getMouseButtonState(int buttonNumber) const {
    return m_mouseButtonStates[buttonNumber];
}
Vector2D* InputHandler::getMousePosition() const {
    return m_mousePosition;
}