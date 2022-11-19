#include "PauseState.h"
#include "Game.h"
#include "MenuState.h"
#include "GameStateMachine.h"
#include "MenuButton.h"
const std::string PauseState::s_pauseID = "PAUSE";
void PauseState::render()
{
    GameState::render();
    TheTextureManager::Instance()->drawText("<< Paused >>", 610, 280, TheGame::Instance()->getRenderer(), 11, 191, 32, 255);
}
bool PauseState::onEnter()
{
    //Ŀ�� ���̱�
    SDL_ShowCursor(SDL_ENABLE);
    loadImage("Assets/resume.png", "resumebutton");
    loadImage("Assets/main.png", "mainbutton");
    GameState::onEnter();
    m_gameObjects.push_back(new MenuButton(new LoaderParams(600, 350, 200, 80, "mainbutton"), s_pauseToMain));
    m_gameObjects.push_back(new MenuButton(new LoaderParams(600, 550, 200, 80, "resumebutton"), s_resumePlay));
    std::cout << "entering PauseState \n";
    return true;
}

bool PauseState::onExit()
{
    //PauseState�� ��������� �����ϸ� �ȵǹǷ� onExit ���� ����
    for (int i = 0; i < m_gameObjects.size(); i++) {
        m_gameObjects[i]->clean();
        delete m_gameObjects[i];
    }
    m_gameObjects.clear();
    execute();
    std::cout << "exiting PauseState \n";
    return true;
}



void PauseState::s_resumePlay()
{
    TheGameStateMachine::Instance()->popState();
    //Ŀ�� �ٽ� �Ⱥ��̰��ϱ�
    SDL_ShowCursor(SDL_DISABLE);
    MusicManager::Instance()->controlMusic(RESUME);
}

void PauseState::s_pauseToMain()
{
    TheGameStateMachine::Instance()->popState();
    TheGameStateMachine::Instance()->popState();
    TheGameStateMachine::Instance()->popState();
    TheGameStateMachine::Instance()->changeState(new MenuState());
    
}
