#pragma once
#include <string>
#include <time.h>
/// <summary>
/// 충돌 가능한 객체들이 상속하는 인터페이스
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
	/// 타이머를 갱신하는 함수
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
	/// 사라져야하는지를 반환하는 함수
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
	/// 클릭되었을경우 동작하는 함수
	/// </summary>
	/// <returns> 클릭된 오브젝트 타입 </returns>
	virtual std::string takeAction() = 0;
	/// <summary>
	/// 사라질때 호출되는 함수
	/// </summary>
	virtual void missAction() = 0;
protected:
	bool isCollision = false;
	float LiveTime;
	//사라지는데 걸리는 시간
	float DisappearTime;
	float LastTime;
	float delay;
	std::string tag;
};