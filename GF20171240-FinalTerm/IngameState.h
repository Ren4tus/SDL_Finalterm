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

	//��� ������ ����
	float asteroidDelay = 0.25f;
	float asteroidTimer;
	//� ������� �ð�
	float asteroidDisapperDelay = 2.0f;


	//�浹������ ��ü���� �����ϴ� ����
	std::vector<GameObject* > m_collObjects;

	//�������̽� ��ġ
	const int PLAY_AREA_X = 50;
	const int PLAY_AREA_Y = 100;

	//� ������
	int ASTEROID_W = 100;
	int ASTEROID_H = 100;

	//ü�� �� ������
	int HEALTHPACK_W = 70;
	int HEALTHPACK_H = 70;

	//��Ȧ ������
	int BLACKHOLE_W = 80;
	int BLACKHOLE_H = 80;

	//����� ��ġ, ũ��
	const int PROGRESS_BAR_X = 900;
	const int PROGRESS_BAR_Y = 30;
	const int PROGRESS_BAR_W = 500;
	const int PROGRESS_BAR_H = 35;

	//���� UI ��ġ
	const int SCORE_BAR_X = 540;
	const int SCORE_BAR_Y = 10;

	//��� ������ ��ġ
	const int MOD_X = 700;
	const int MOD_Y = 30;

	//������ �ð�, ����� �ð�
	float endTime;
	float progressTime;
	float lastTime;

	//��Ȧ ȿ���� ���� �ð�
	float blackholeTime;
};