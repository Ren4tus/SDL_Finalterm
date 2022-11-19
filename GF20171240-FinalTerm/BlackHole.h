#pragma once
#include "ICollisionable.h"
#include "SDLGameObject.h"
#include <time.h>
class BlackHole : public SDLGameObject, public ICollisionable
{
public:
	BlackHole(const LoaderParams* pParams, float delayValue) : SDLGameObject(pParams) {
		clock_t nowTime = clock();
		LiveTime = (nowTime / (float)CLOCKS_PER_SEC);
		DisappearTime = 0.0f;
		LastTime = (nowTime / (float)CLOCKS_PER_SEC);
		delay = delayValue;

		tag = "BlackHole";
	}
	~BlackHole() {}


	virtual std::string takeAction();
	virtual void missAction();
private:
};