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
	//���� �׸���
	nowNode->drawLine();

	//��� �׸���
	for (int i = 0; i < NodeTree.size(); i++) {
		NodeTree[i]->draw();
	}
	//�۾��� ������ �ʰ� ��带 �� �׸� ���� ��� ���� ����
	for (int i = 0; i < NodeTree.size(); i++) {
		NodeTree[i]->drawIndicater();
	}
	//���� ��ġ ǥ���ϱ�
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
	//���� ������ ��带 ����
	for (int i = 0; i < nodeNum; i++) {
		NodeTree.push_back(new MapNode(new LoaderParams(ui_x + i * 60, ui_y + dis(gen), 256, 256, "Node"), s_doNothing));
		NodeTree.back()->setModifier(50, 50);
	}

	//�Ÿ��� ����ؼ� ��峢�� �����Ѵ�
	for (int i = 0; i < nodeNum; i++) {
		for (int j = i + 1; j < nodeNum && j < i + 4; j++) {
			if (400 > abs(NodeTree[i]->getPosition().getY() - NodeTree[j]->getPosition().getY())) {
				NodeTree[i]->addLinkNode(NodeTree[j]);
				NodeTree[j]->addLinkNode(NodeTree[i]);
			}
		}
	}

	//�ϳ��� ������� ���� ���� �ٷ� �� ���� �����Ѵ�
	for (int i = 0; i < nodeNum; i++) {
		if (NodeTree[i]->getLinkedNode().size() == 0) {
			//������ ����� ���� ���� ���� �����Ѵ�
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
	//�����ϰ� ����� Ÿ���� ����
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
	//���������� ������������ ���Ѵ�
	std::uniform_int_distribution<int> randValue(0, 4);
	nowNode = NodeTree[randValue(gen)];
	nowNode->setType(START);
	NodeTree[NodeTree.size() - randValue(gen) - 1]->setType(END);

	//���� ������ ����� ��常 �۵��ϵ��� �ݹ� �Լ��� ����
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

	//��� ����� �ݹ� �Լ��� ����
	for (int i = 0; i < MapManager::Instance()->NodeTree.size(); i++) {
		MapManager::Instance()->NodeTree[i]->setCallback(s_doNothing);
	}
	//���� ���� ����� ��忡�Ը� �ݹ� �Լ��� ���
	for (int i = 0; i < MapManager::Instance()->nowNode->getLinkedNode().size(); i++) {
		MapManager::Instance()->nowNode->getLinkedNode()[i]->setCallback(s_mapToIngame);
	}
}

void MapManager::s_doNothing(unsigned int type)
{
	std::cout << "Unconnected node clicked\n";
	return;
}
