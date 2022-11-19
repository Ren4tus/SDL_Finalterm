#pragma once
#include <string>
#include <time.h>
/// <summary>
/// �浹 ������ ��ü���� ����ϴ� �������̽�
/// </summary>
class ICollisionable abstract
{
public:
	virtual void EneterCollision() { isCollision = true; }
	virtual void ExitCollision() { isCollision = false; }
	virtual bool getCollisionState() { return isCollision; }
	virtual float getLiveTime() { return LiveTime; }
	virtual float getDisapperTime() { return DisappearTime; }
	/// <summary>
	/// Ÿ�̸Ӹ� �����ϴ� �Լ�
	/// </summary>
	virtual void resetTimer() {

		clock_t nowTime = clock();

		if ((nowTime / (float)CLOCKS_PER_SEC) - LastTime > 0.1f) {
			LastTime = (nowTime / (float)CLOCKS_PER_SEC);
			DisappearTime += 0.1f;
		}
		LiveTime = ((nowTime / (float)CLOCKS_PER_SEC) - LiveTime);


	}
	/// <summary>
	/// ��������ϴ����� ��ȯ�ϴ� �Լ�
	/// </summary>
	/// <returns></returns>
	virtual bool getDissapperState() {
		if (delay < DisappearTime) {
			return true;
		}
		return false;
	}
	virtual void setDelay(float val) { delay = val; }
	virtual std::string getTag() { return tag; }
	/// <summary>
	/// Ŭ���Ǿ������ �����ϴ� �Լ�
	/// </summary>
	/// <returns> Ŭ���� ������Ʈ Ÿ�� </returns>
	virtual std::string takeAction() = 0;
	/// <summary>
	/// ������� ȣ��Ǵ� �Լ�
	/// </summary>
	virtual void missAction() = 0;
protected:
	bool isCollision = false;
	float LiveTime;
	//������µ� �ɸ��� �ð�
	float DisappearTime;
	float LastTime;
	float delay;
	std::string tag;
};