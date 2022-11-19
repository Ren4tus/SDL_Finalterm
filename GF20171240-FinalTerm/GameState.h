#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "MusicManager.h"
class GameState {
public:
	GameState();
	~GameState() { std::cout << "delete state \n"; }
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const = 0;
	/// <summary>
	/// @brief 객체의 삭제 시점을 늦추는 함수
	/// </summary>
	virtual void execute() { toBeExecuted = true; }
	/// <summary>
	/// @brief 객체가 삭제되어야하는지 확인하는 함수
	/// </summary>
	/// <returns> 삭제 예정이면 true </returns>
	virtual bool getExecute() const { return toBeExecuted; }
	/// <summary>
	/// @brief 에셋을 로드하는 함수
	/// </summary>
	/// <param name="fileName"> 파일의 경로</param>
	/// <param name="name"> 파일에 접근하기 위한 이름</param>
	virtual void loadImage(std::string fileName,std::string name);
protected:
	std::vector<GameObject*> m_gameObjects;
	/// <summary>
	/// @brief 파일의 경로와 이름을 저장하는 배열
	/// </summary>
	std::vector<std::vector<std::string>> fileNames;
	bool toBeExecuted = false;
};