#pragma once
#include "ICollisionable.h"
#include "SDLGameObject.h"
#include <time.h>
class Asteroid : public SDLGameObject,public ICollisionable
{
public:
	Asteroid(const LoaderParams* pParams,float delayValue) : SDLGameObject(pParams) {
		clock_t nowTime = clock();
		LiveTime = (nowTime / (float)CLOCKS_PER_SEC);
		DisappearTime = 0.0f;
		LastTime = (nowTime / (float)CLOCKS_PER_SEC);
		delay = delayValue;

		tag = "Asteroid";
	}
	~Asteroid() {}


	virtual std::string takeAction();
	virtual void missAction();
private:
};