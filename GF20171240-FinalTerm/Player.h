#pragma once
#include <vector>
#include "SDLGameObject.h"
class Player
{
public:
    Player();
    void draw();
    void update();
    void clean();

    SDLGameObject* getCursor() { return cursor; }
private:
    SDLGameObject* cursor;
};
