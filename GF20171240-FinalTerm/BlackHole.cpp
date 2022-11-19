#include "BlackHole.h"
#include "MusicManager.h"
std::string BlackHole::takeAction()
{
    TheMusicManager::Instance()->playEffectSound("blackhole");
    return tag;
}

void BlackHole::missAction()
{
    //do nothing
}
