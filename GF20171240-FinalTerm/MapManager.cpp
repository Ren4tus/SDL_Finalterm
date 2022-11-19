#include "MapManager.h"
#include <random>
#include "MapNode.h"
#include <math.h>
#include "Game.h"
#include <iostream>
#include "IngameState.h"
MapManager* MapManager:: s_pInstance = 0;
void MapManager::drawMap()
{
	//간선 그리기
	nowNode->drawLine();

	//노드 그리기
	for (int i = 0; i < NodeTree.size(); i++) {
		NodeTree[i]->draw();
	}
	//글씨가 묻히지 않게 노드를 다 그린 위에 노드 정보 적기
	for (int i = 0; i < NodeTree.size(); i++) {
		NodeTree[i]->drawIndicater();
	}
	//현재 위치 표시하기
	TheTextureManager::Instance()->drawText("Now", nowNode->getPosition().getX() + 15, nowNode->getPosition().getY() + 40, TheGame::Instance()->getRenderer(), 11, 191, 32, 255);
}

bool MapManager::isEmpty()
{
	if (NodeTree.size() == 0)
		return true;
	else
		return false;
}

void MapManager::createNewMap()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 700);
	//랜덤 범위의 노드를 생성
	for (int i = 0; i < nodeNum; i++) {
		NodeTree.push_back(new MapNode(new LoaderParams(ui_x + i * 60, ui_y + dis(gen), 256, 256, "Node"), s_doNothing));
		NodeTree.back()->setModifier(50, 50);
	}

	//거리를 계산해서 노드끼리 연결한다
	for (int i = 0; i < nodeNum; i++) {
		for (int j = i + 1; j < nodeNum && j < i + 4; j++) {
			if (400 > abs(NodeTree[i]->getPosition().getY() - NodeTree[j]->getPosition().getY())) {
				NodeTree[i]->addLinkNode(NodeTree[j]);
				NodeTree[j]->addLinkNode(NodeTree[i]);
			}
		}
	}

	//하나도 연결되지 못한 노드는 바로 앞 노드와 연결한다
	for (int i = 0; i < nodeNum; i++) {
		if (NodeTree[i]->getLinkedNode().size() == 0) {
			//마지막 노드인 경우는 뒤의 노드와 연결한다
			if (i == nodeNum - 1) {
				NodeTree[i]->addLinkNode(NodeTree[i - 1]);
				NodeTree[i - 1]->addLinkNode(NodeTree[i]);
			}
			else {
				NodeTree[i]->addLinkNode(NodeTree[i + 1]);
				NodeTree[i + 1]->addLinkNode(NodeTree[i]);
			}
		}

	}
	//랜덤하게 노드의 타입을 결정
	std::uniform_int_distribution<int> nodeRand(0, 2);
	for (int i = 0; i < nodeNum; i++) {
		switch (nodeRand(gen))
		{
		case 0:
			NodeTree[i]->setType(NONE);
			break;
		case 1:
			NodeTree[i]->setType(HARDROCK);
			break;
		case 2:
			NodeTree[i]->setType(DOUBLETIME);
			break;
		default:
			break;
		}
	}
	//시작지점과 마지막지점을 정한다
	std::uniform_int_distribution<int> randValue(0, 4);
	nowNode = NodeTree[randValue(gen)];
	nowNode->setType(START);
	NodeTree[NodeTree.size() - randValue(gen) - 1]->setType(END);

	//현재 지점과 연결된 노드만 작동하도록 콜백 함수를 적용
	for (int i = 0; i < nowNode->getLinkedNode().size(); i++) {
		nowNode->getLinkedNode()[i]->setCallback(s_mapToIngame);
	}
	
}
void MapManager::update()
{
	for (int i = 0; i < NodeTree.size(); i++) {
		NodeTree[i]->update();
	}
}
void MapManager::clean()
{
	for (int i = 0; i < NodeTree.size(); i++) {
		NodeTree[i]->getLinkedNode().clear();
		delete NodeTree[i];
	}
	NodeTree.clear();
}
void MapManager::s_mapToIngame(unsigned int type)
{
	std::cout << "node button clicked\n";
	TheGameStateMachine::Instance()->changeState(new IngameState(type));
	MapManager::Instance()->nowNode = MapManager::Instance()->clickedNode;

	//모든 노드의 콜백 함수를 해제
	for (int i = 0; i < MapManager::Instance()->NodeTree.size(); i++) {
		MapManager::Instance()->NodeTree[i]->setCallback(s_doNothing);
	}
	//현재 노드와 연결된 노드에게만 콜백 함수를 등록
	for (int i = 0; i < MapManager::Instance()->nowNode->getLinkedNode().size(); i++) {
		MapManager::Instance()->nowNode->getLinkedNode()[i]->setCallback(s_mapToIngame);
	}
}

void MapManager::s_doNothing(unsigned int type)
{
	std::cout << "Unconnected node clicked\n";
	return;
}
