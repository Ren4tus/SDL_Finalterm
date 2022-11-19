#pragma once
#include <vector>
#include "MapNode.h"
class MapManager
{
public:

	~MapManager()
	{
	}
	static MapManager* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new MapManager();
		}
		return s_pInstance;
	}

	void drawMap();
	bool isEmpty();
	void update();
	void clean();
	/// <summary>
	/// @brief 노드 트리 전체를 생성하는 함수
	/// </summary>
	void createNewMap();
	/// <summary>
	/// @brief 클릭한 노드가 무엇인지 전달하는 함수
	/// </summary>
	/// <param name="node"> 클락한 노드 주소 </param>
	void nodeClickFeedback(MapNode* node) { clickedNode = node; }
private:
	MapManager(){}
	static MapManager* s_pInstance;
	MapNode* nowNode;
	int ui_x = 300;
	int ui_y = 100;
	const int nodeNum = 15;
	std::vector<MapNode*> NodeTree;

	MapNode* clickedNode;
	static void s_mapToIngame(unsigned int type);
	static void s_doNothing(unsigned int type);
};
