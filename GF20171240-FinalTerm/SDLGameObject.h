#pragma once
#include "GameObject.h"
#include "Vector2D.h"
class SDLGameObject : public GameObject
{
public:
	SDLGameObject(const LoaderParams* pParams);

	~SDLGameObject()
	{
	}

	virtual void draw();
	virtual void update();
	virtual void clean();

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	virtual Vector2D getPosition() { return m_position; }
	virtual void setPosition(float x, float y) { m_position.setX(x); m_position.setY(y); }
	/// <summary>
	/// �̹����� ũ��� �׸������ ũ�Ⱑ �ٸ� �� ������ ���� ����ϴ� �Լ�
	/// </summary>
	virtual void setModifier(int w, int h, int row = -1, int frame = -1, int numFrame = -1);
	
protected:
	std::string m_textureID;
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;
};
