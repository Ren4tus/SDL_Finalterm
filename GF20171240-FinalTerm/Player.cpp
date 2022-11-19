#include "Player.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameData.h"
#include <string>

Player::Player()
{
   
    int w, h;
    TheTextureManager::Instance()->imageQuerySize("aimPoint", &w, &h);
    cursor = new SDLGameObject(new LoaderParams(0, 0, w, h, "aimPoint"));
}

void Player::draw()
{
    cursor->draw();
}
void Player::update()
{
    
    cursor->setPosition(InputHandler::Instance()->getMousePosition()->getX()-(cursor->getDestW()/2), 
        InputHandler::Instance()->getMousePosition()->getY() - (cursor->getDestH() / 2));

}

void Player::clean()
{
    delete cursor;
}
