#pragma once
#include "Vector2D.h"
#include <string>
#include <vector>
#include "SDLGameObject.h"
/// <summary>
/// @brief 맵에서 사용되는 노드 클래스
/// </summary>
class MapNode : public SDLGameObject
{
public:
	/// <summary>
	/// @brief 노드는 클릭했을 때 이벤트를 등록할 콜백 함수를 인자로 받는다.
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
	/// 콜백 함수를 등록하는 함수
	/// </summary>
	virtual void setCallback(void(*callback)(unsigned int type)) { m_nodeCallback = callback; }
	/// <summary>
	/// 어떤 노드인지 텍스트로 표시
	/// </summary>
	void drawIndicater();
private:
	//노드의 이벤트 타입
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
