#pragma once
#include <vector>
#include <string>
#include "GameObject.h"

/// <summary>
/// ���ֹ߼� ���� �������� �����ϴ� Ŭ����
/// </summary>
class GameData
{
public:

	~GameData()
	{
	}

	static GameData* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new GameData();
			
		}
		return s_pInstance;
	}
	void initGameData();
	int getHP() const { return HP; }
	void setHP(int val) { val<=100 ? HP = val : HP=100; }
	int getScore() const { return score; }
	void setScore(int val) { score = val; }
private:
	GameData();
	static GameData* s_pInstance;
	int HP;
	int score;

};
