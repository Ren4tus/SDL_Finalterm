#include "IngameState.h"
#include "MapNode.h"
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include <random>
#include "MapManager.h"
#include "GameData.h"
#include "GameOverState.h"
#include "Asteroid.h"
#include "PauseState.h"
#include "PlayState.h"
#include "GameClearState.h"
#include "HealthPack.h"
#include "BlackHole.h"
const std::string IngameState::s_menuID = "INGAME";
IngameState::IngameState(unsigned int type) : eventType(type)
{
	clock_t nowTime = clock();
	asteroidTimer = (float)(nowTime/CLOCKS_PER_SEC);
	lastTime = (float)(nowTime / CLOCKS_PER_SEC);
	endTime = 1.0f;
	progressTime = 0.0f;		
	asteroidDelay = 0.25f;
	asteroidDisapperDelay = 2.0f;
	ASTEROID_W = 100;
	ASTEROID_H = 100;

	//�̺�Ʈ Ÿ�Կ� ���� ����
	if (type == HARDROCK) {
		ASTEROID_W = 50;
		ASTEROID_H = 50;
		
	}
	else if (type == DOUBLETIME) {
		asteroidDelay = 0.20f;
	}
	else if (type == END) {
		endTime = 30.0f;
		ASTEROID_W = 50;
		ASTEROID_H = 50;
		asteroidDelay = 0.20f;
	}
}
void IngameState::update()
{
	GameState::update();
	createObjects();
	player->update();
	if (progress()) {
		if (!(eventType == END)) {
			TheGameStateMachine::Instance()->changeState(new PlayState());

		}
		else {
			TheGameStateMachine::Instance()->changeState(new GameClearState());
		}
	}
	if (blackholeTime > 0.0f) {
		blackholeEffect();
	}

	for (int i = 0; i < m_collObjects.size(); i++) {
		//Ŀ���� �浹�ߴ��� �ƴ��� üũ
		if (checkCollision(dynamic_cast<SDLGameObject*>(m_collObjects[i]), player->getCursor()) &&
			dynamic_cast<ICollisionable*>(m_collObjects[i])->getCollisionState() == false)
		{
			dynamic_cast<ICollisionable*>(m_collObjects[i])->EneterCollision();
		}
		else if (!checkCollision(dynamic_cast<SDLGameObject*>(m_collObjects[i]), player->getCursor())) {
			dynamic_cast<ICollisionable*>(m_collObjects[i])->ExitCollision();
		}

		//Ÿ�̸�
		dynamic_cast<ICollisionable*>(m_collObjects[i])->resetTimer();
	}


	// ���� �� ���͸� �����ϸ� ������ �߻��� �� �����Ƿ� iterator ���
	std::vector<GameObject*>::iterator iterPos = m_collObjects.begin();

	//����� Ŭ���ߴ��� Ȯ���ϴ� ����
	bool missHit = true;
	if (InputHandler::Instance()->isKeyOneDown(SDL_SCANCODE_Z) || InputHandler::Instance()->isKeyOneDown(SDL_SCANCODE_X)) {
		TheMusicManager::Instance()->playEffectSound("hitSound");
		while (iterPos != m_collObjects.end()) {
			if (dynamic_cast<ICollisionable*>(m_collObjects.at(std::distance(m_collObjects.begin(), iterPos)))->getCollisionState() == true) {
				//������Ʈ�� ���� �����ϰ� ���� ��Ȧ�̶�� Ư���� ����
				if (dynamic_cast<ICollisionable*>(m_collObjects.at(std::distance(m_collObjects.begin(), iterPos)))->takeAction() == "BlackHole") {
					blackholeTime = 2.0f;
				}
				
				delete m_collObjects.at(std::distance(m_collObjects.begin(), iterPos));
				iterPos = m_collObjects.erase(iterPos);
				//� ������Ʈ�� Ŭ���� ������ ���
				missHit = false;
				break;
			}
			++iterPos;
		}
		//�ƹ� ��ü�͵� �浹���� �ʾҴٸ� ����
		if (missHit) {
			GameData::Instance()->setScore(GameData::Instance()->getScore() - 5);
		}
	}

	
	//���� �ð��� ���� ��� ����
	while (iterPos != m_collObjects.end()) {
		if(dynamic_cast<ICollisionable*>(m_collObjects.at(std::distance(m_collObjects.begin(), iterPos)))->getDissapperState())
		{
			dynamic_cast<ICollisionable*>(m_collObjects.at(std::distance(m_collObjects.begin(), iterPos)))->missAction();
			delete m_collObjects.at(std::distance(m_collObjects.begin(), iterPos));
			iterPos = m_collObjects.erase(iterPos);
			break;
		}
		++iterPos;
	}

	//ESC�� ������ ����
	if (InputHandler::Instance()->isKeyOneDown(SDL_SCANCODE_ESCAPE)) {
		TheGameStateMachine::Instance()->pushState(new PauseState());
		MusicManager::Instance()->controlMusic(PAUSE);
	}

	//ü���� 0 ���ϸ� ���ӿ���
	if (GameData::Instance()->getHP() <= 0) {
		TheGameStateMachine::Instance()->changeState(new GameOverState());
	}

}

void IngameState::render()
{

	GameState::render();
	//���� �������̽��� �׸���
	TheTextureManager::Instance()->drawRect(PLAY_AREA_X - 25, PLAY_AREA_Y, Game::Instance()->getWindowWidth() - PLAY_AREA_X*2 + 50, Game::Instance()->getWindowHeight() - PLAY_AREA_Y*2,
		TheGame::Instance()->getRenderer(), 86, 86, 86, 170, true);
	TheTextureManager::Instance()->drawRect(PLAY_AREA_X - 25, PLAY_AREA_Y, Game::Instance()->getWindowWidth() - PLAY_AREA_X*2 + 50, Game::Instance()->getWindowHeight() - PLAY_AREA_Y*2,
		TheGame::Instance()->getRenderer(), 144, 144, 114, 255);

	//HP�������� �׸���
	for (int i = 0; i * 5 < GameData::Instance()->getHP(); i++) {
		TheTextureManager::Instance()->drawRect((i * 24) + 15, 20, 20, 40, TheGame::Instance()->getRenderer(), 120, 255, 120, 255, true);
		TheTextureManager::Instance()->drawRect((i * 24) + 15, 20, 20, 40, TheGame::Instance()->getRenderer(), 120, 255, 120, 255);
	}

	//HP�ٸ� �׸���
	TheTextureManager::Instance()->draw("Hull", 10, 10, 490, 56, TheGame::Instance()->getRenderer());

	//���ھ� ���ڸ� �׸���
	TheTextureManager::Instance()->drawText(std::to_string(GameData::Instance()->getScore()), SCORE_BAR_X+50, SCORE_BAR_Y+13, TheGame::Instance()->getRenderer(), 76, 228, 213, 255);

	//���� ������ �׸���
	TheTextureManager::Instance()->drawRect(PROGRESS_BAR_X, PROGRESS_BAR_Y, PROGRESS_BAR_W, PROGRESS_BAR_H, TheGame::Instance()->getRenderer(), 255, 255, 255, 255, true);
	TheTextureManager::Instance()->drawRect(PROGRESS_BAR_X, PROGRESS_BAR_Y, PROGRESS_BAR_W * (progressTime / endTime) , PROGRESS_BAR_H, TheGame::Instance()->getRenderer(), 120, 255, 120, 255, true);

	//����ٸ� �׸���
	TheTextureManager::Instance()->drawRect(PROGRESS_BAR_X, PROGRESS_BAR_Y, PROGRESS_BAR_W, PROGRESS_BAR_H, TheGame::Instance()->getRenderer(), 0, 0, 0, 255);

	//�浹 ������ ��ü���� �׸���
	for (int i = 0; i < m_collObjects.size(); i++) {
		m_collObjects[i]->draw();
	}
	//Ŀ���� �׸���
	player->draw();
}

bool IngameState::onEnter()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> randBG(0, 1);
	switch (randBG(gen)) {
		case 0:
			loadImage("Assets/UI/bg/inGame_BG_1.jpg", "InGameBG");
			break;
		case 1:
			loadImage("Assets/UI/bg/inGame_BG_2.jpg", "InGameBG");
			break;
		default:
			break;
	}

	loadImage("Assets/UI/aimPoint.png", "aimPoint");
	loadImage("Assets/UI/healthPack.png", "healthPack");
	loadImage("Assets/UI/blackhole.png", "blackhole");
	loadImage("Assets/UI/HullBar.png", "Hull");
	loadImage("Assets/UI/ScoreUI.png", "ScoreUI");
	if (eventType == HARDROCK) {
		loadImage("Assets/UI/asteroid50.png", "asteroid");
		loadImage("Assets/UI/hardrock.PNG", "MOD");
	}
	else if (eventType == DOUBLETIME) {
		loadImage("Assets/UI/doubleTime.PNG", "MOD");
		loadImage("Assets/UI/asteroid100.png", "asteroid");
	}
	else if (eventType == END) {
		loadImage("Assets/UI/hardrock.PNG", "MOD2");
		loadImage("Assets/UI/doubleTime.PNG", "MOD");
		loadImage("Assets/UI/asteroid50.png", "asteroid");
	}
	else {
		loadImage("Assets/UI/asteroid100.png", "asteroid");
	}

	if (!GameState::onEnter()) {return false;}

	//���� ���� ����
	TheMusicManager::Instance()->controlMusic(HALT);
	TheMusicManager::Instance()->clearMusic();
	//���� �ε�
	std::uniform_int_distribution<int> randBGM(0, 4);
	//������� �������� ����
	switch (randBGM(gen)) {
	case 0:
		TheMusicManager::Instance()->loadAudio("Assets/Audio/ingameBGM2.mp3", "",true);
		break;
	case 1:
		TheMusicManager::Instance()->loadAudio("Assets/Audio/ingameBGM3.mp3", "", true);
		break;
	case 2:
		TheMusicManager::Instance()->loadAudio("Assets/Audio/ingameBGM4.mp3", "", true);
		break;
	case 3:
		TheMusicManager::Instance()->loadAudio("Assets/Audio/ingameBGM5.mp3", "", true);
		break;
	case 4:
		TheMusicManager::Instance()->loadAudio("Assets/Audio/ingameBGM6.mp3", "", true);
		break;
	}
	TheMusicManager::Instance()->loadAudio("Assets/Audio/hit.wav", "hitSound", false);
	TheMusicManager::Instance()->loadAudio("Assets/Audio/missSound.wav", "missSound", false);
	TheMusicManager::Instance()->loadAudio("Assets/Audio/ping.mp3", "healthPack", false);
	TheMusicManager::Instance()->loadAudio("Assets/Audio/blackhole.wav", "blackhole", false);
	//������� ����
	TheMusicManager::Instance()->controlMusic(PLAY);

	int w, h;
	m_gameObjects.push_back(new SDLGameObject(new LoaderParams(0, 0, TheGame::Instance()->getWindowWidth(), TheGame::Instance()->getWindowHeight(), "InGameBG")));
	TheTextureManager::Instance()->imageQuerySize("ScoreUI", &w, &h);
	m_gameObjects.push_back(new SDLGameObject(new LoaderParams(SCORE_BAR_X, SCORE_BAR_Y, w, h, "ScoreUI")));

	//��� ������ �ε�
	if (eventType == HARDROCK || eventType == DOUBLETIME) {
		TheTextureManager::Instance()->imageQuerySize("MOD", &w, &h);
		m_gameObjects.push_back(new SDLGameObject(new LoaderParams(MOD_X, MOD_Y, w, h, "MOD")));
	}
	else if (eventType == END) {
		TheTextureManager::Instance()->imageQuerySize("MOD", &w, &h);
		m_gameObjects.push_back(new SDLGameObject(new LoaderParams(MOD_X, MOD_Y, w, h, "MOD")));
		TheTextureManager::Instance()->imageQuerySize("MOD2", &w, &h);
		m_gameObjects.push_back(new SDLGameObject(new LoaderParams(MOD_X+60, MOD_Y, w, h, "MOD2")));
	}

	player = new Player();

	//Ŀ�� �����
	SDL_ShowCursor(SDL_DISABLE);

	


	
	std::cout << "entering IngameState\n";
	return true;
}

bool IngameState::onExit()
{
	GameState::onExit();
	for (int i = 0; i < m_collObjects.size(); i++) {
		m_collObjects[i]->clean();
		delete m_collObjects[i];
	}
	m_collObjects.clear();

	//collObjects�� ������Ʈ�� �������� ���� ���¿��� ����� ���� �����Ƿ�
	TheTextureManager::Instance()->clearFromTextureMap("asteroid");
	TheTextureManager::Instance()->clearFromTextureMap("healthPack");
	TheTextureManager::Instance()->clearFromTextureMap("blackhole");
	TheTextureManager::Instance()->clearFromTextureMap("Hull");
	TheTextureManager::Instance()->clearFromTextureMap("MOD");
	TheTextureManager::Instance()->clearFromTextureMap("MOD2");
	TheMusicManager::Instance()->clearEffectSound("hitSound");
	TheMusicManager::Instance()->clearEffectSound("missSound");
	TheMusicManager::Instance()->clearEffectSound("healthPack");
	TheMusicManager::Instance()->clearEffectSound("blackhole");
	//Ŀ�� ���̱�
	SDL_ShowCursor(SDL_ENABLE);
	return true;
}


void IngameState::createObjects()
{
	clock_t nowTime = clock();
	float nowTimeSec = (nowTime / (float)CLOCKS_PER_SEC);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> healRand(0, 40);
	std::uniform_int_distribution<int> randPositionX(PLAY_AREA_X, Game::Instance()->getWindowWidth() - PLAY_AREA_X * 2);
	std::uniform_int_distribution<int> randPositionY(PLAY_AREA_Y, Game::Instance()->getWindowHeight() - PLAY_AREA_Y * 2);
	//������ �ð����� ������Ʈ ����
	if (nowTimeSec > asteroidTimer + asteroidDelay) {

		//ü�� ���� �����ϰ� ����
		if (healRand(gen) == 0) {
			m_collObjects.push_back(new BlackHole(new LoaderParams(randPositionX(gen), randPositionY(gen), HEALTHPACK_W, HEALTHPACK_H, "blackhole"), asteroidDisapperDelay));
		}
		else if (healRand(gen) < 5) {
			m_collObjects.push_back(new HealthPack(new LoaderParams(randPositionX(gen), randPositionY(gen), HEALTHPACK_W, HEALTHPACK_H, "healthPack"), asteroidDisapperDelay));

		}
		
		//��� �׻� ����
		
		m_collObjects.push_back(new Asteroid(new LoaderParams(randPositionX(gen), randPositionY(gen), ASTEROID_W, ASTEROID_H, "asteroid"), asteroidDisapperDelay));

		asteroidTimer = nowTimeSec;
	}
	
}
void IngameState::resetObjectTimer()
{
	for (int i = 0; i < m_collObjects.size(); i++) {
		dynamic_cast<ICollisionable*>(m_collObjects[i])->resetTimer();
	}
}
bool IngameState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB, rightA, rightB;
	int topA, topB, bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	if (bottomA <= topB) return false;
	if (topA >= bottomB) return false;
	if (rightA <= leftB) return false;
	if (leftA >= rightB) return false;

	return true;
}

bool IngameState::progress()
{

	if (endTime < progressTime)
		return true;

	// 0.1�ʸ��� ����� ������ �ø���
	clock_t nowTime = clock();
	if ((nowTime / (float)CLOCKS_PER_SEC) - lastTime > 0.1f) {
		lastTime = (nowTime / (float)CLOCKS_PER_SEC);
		progressTime += 0.1f;
		blackholeTime - 0.1f > 0.0f ? blackholeTime -= 0.1f : blackholeTime = 0.0f;
	}
	
	return false;
}

void IngameState::blackholeEffect()
{
	for (int i = 0; i < m_collObjects.size(); i++) {
		if (dynamic_cast<ICollisionable*>(m_collObjects[i])->getTag() == "Asteroid") {

			//��� ��� ���� ���콺�� �̵��ϵ��� ���
			Vector2D moveVector = player->getCursor()->getPosition() - dynamic_cast<SDLGameObject*>(m_collObjects[i])->getPosition();
			moveVector.normalize();
			
			dynamic_cast<SDLGameObject*>(m_collObjects[i])->setPosition(
				dynamic_cast<SDLGameObject*>(m_collObjects[i])->getPosition().getX() + moveVector.getX() * 0.3f,
				dynamic_cast<SDLGameObject*>(m_collObjects[i])->getPosition().getY() + moveVector.getY() * 0.3f
			);
		}
	}
}
