#include "GameData.h"
GameData* GameData::s_pInstance = 0;
void GameData::initGameData()
{
	score = 0;
	HP = 100;
}
GameData::GameData()
{
	score = 0;
	HP = 100;
}
