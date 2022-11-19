#pragma once
#include "Vector2D.h"
#include <string>
#include <vector>
#include "SDLGameObject.h"
/// <summary>
/// @brief �ʿ��� ���Ǵ� ��� Ŭ����
/// </summary>
class MapNode : public SDLGameObject
{
public:
	/// <summary>
	/// @brief ���� Ŭ������ �� �̺�Ʈ�� ����� �ݹ� �Լ��� ���ڷ� �޴´�.
	/// </summary>
	MapNode(const LoaderParams* pParams, void(*callback)(unsigned int)) : SDLGameObject(pParams), m_nodeCallback(callback)
	{

	}

	~MapNode()
	{
	}

	virtual void draw();
	virtual void update();
	void drawLine();
	std::vector<MapNode*> getLinkedNode() {
		return linkedNode;
	}
	void addLinkNode(MapNode* link) {
		linkedNode.push_back(link);
	}
	void setType(unsigned int data) { type = data; }
	unsigned int getType() { return type; }
	/// <summary>
	/// �ݹ� �Լ��� ����ϴ� �Լ�
	/// </summary>
	virtual void setCallback(void(*callback)(unsigned int type)) { m_nodeCallback = callback; }
	/// <summary>
	/// � ������� �ؽ�Ʈ�� ǥ��
	/// </summary>
	void drawIndicater();
private:
	//����� �̺�Ʈ Ÿ��
	unsigned int type;
	std::vector<MapNode*> linkedNode;
	unsigned const int markerSize = 80;
	unsigned const int realMarkerSize = 512;
	void(*m_nodeCallback)(unsigned int);
	bool m_bReleased = true;
};

enum NodeType {
	BLACKHOLE,DOUBLETIME,HARDROCK,START,END,NONE
};
