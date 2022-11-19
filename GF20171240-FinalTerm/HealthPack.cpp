#include "HealthPack.h"
#include "GameData.h"
#include "MusicManager.h"
std::string HealthPack::takeAction()
{
	TheMusicManager::Instance()->playEffectSound("healthPack");
	GameData::Instance()->setHP(GameData::Instance()->getHP() + 5);

	return tag;
}

void HealthPack::missAction()
{
	//do nothing
}
