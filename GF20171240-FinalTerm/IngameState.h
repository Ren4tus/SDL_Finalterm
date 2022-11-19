#pragma once
#include "GameState.h"
#include "Player.h"
#include <time.h>
#include <map>
#include "ICollisionable.h"
class IngameState : public GameState {
public:
	IngameState(unsigned int type);
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return s_menuID; }

	
	void createObjects();
	void resetObjectTimer();
	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);
	bool progress();
	void blackholeEffect();
private:
	static const std::string s_menuID;
	unsigned int eventType;
	Player* player;

	//운석이 나오는 간격
	float asteroidDelay = 0.25f;
	float asteroidTimer;
	//운석 사라지는 시간
	float asteroidDisapperDelay = 2.0f;


	//충돌가능한 객체들을 저장하는 벡터
	std::vector<GameObject* > m_collObjects;

	//인터페이스 위치
	const int PLAY_AREA_X = 50;
	const int PLAY_AREA_Y = 100;

	//운석 사이즈
	int ASTEROID_W = 100;
	int ASTEROID_H = 100;

	//체력 팩 사이즈
	int HEALTHPACK_W = 70;
	int HEALTHPACK_H = 70;

	//블랙홀 사이즈
	int BLACKHOLE_W = 80;
	int BLACKHOLE_H = 80;

	//진행바 위치, 크기
	const int PROGRESS_BAR_X = 900;
	const int PROGRESS_BAR_Y = 30;
	const int PROGRESS_BAR_W = 500;
	const int PROGRESS_BAR_H = 35;

	//점수 UI 위치
	const int SCORE_BAR_X = 540;
	const int SCORE_BAR_Y = 10;

	//모드 아이콘 위치
	const int MOD_X = 700;
	const int MOD_Y = 30;

	//끝나는 시간, 진행된 시간
	float endTime;
	float progressTime;
	float lastTime;

	//블랙홀 효과가 남은 시간
	float blackholeTime;
};