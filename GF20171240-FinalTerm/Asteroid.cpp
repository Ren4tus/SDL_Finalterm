#include "Asteroid.h"
#include "GameData.h"
#include "MusicManager.h"

std::string Asteroid::takeAction()
{
	GameData::Instance()->setScore(GameData::Instance()->getScore() + 10);

	return tag;
}

void Asteroid::missAction()
{
	TheMusicManager::Instance()->playEffectSound("missSound");
	GameData::Instance()->setHP(GameData::Instance()->getHP() - 2);
}
