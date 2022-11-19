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
	/// @brief ��ü�� ���� ������ ���ߴ� �Լ�
	/// </summary>
	virtual void execute() { toBeExecuted = true; }
	/// <summary>
	/// @brief ��ü�� �����Ǿ���ϴ��� Ȯ���ϴ� �Լ�
	/// </summary>
	/// <returns> ���� �����̸� true </returns>
	virtual bool getExecute() const { return toBeExecuted; }
	/// <summary>
	/// @brief ������ �ε��ϴ� �Լ�
	/// </summary>
	/// <param name="fileName"> ������ ���</param>
	/// <param name="name"> ���Ͽ� �����ϱ� ���� �̸�</param>
	virtual void loadImage(std::string fileName,std::string name);
protected:
	std::vector<GameObject*> m_gameObjects;
	/// <summary>
	/// @brief ������ ��ο� �̸��� �����ϴ� �迭
	/// </summary>
	std::vector<std::vector<std::string>> fileNames;
	bool toBeExecuted = false;
};