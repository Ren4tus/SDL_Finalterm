#pragma once
#include <vector>
#include "MusicManager.h"
#include <SDL_mixer.h>
#include <vector>
#include <map>
#include <string>
#include <SDL.h>
class MusicManager
{
public:

	~MusicManager()
	{
	}
	static MusicManager* Instance() {
		if (s_pInstance == 0) {
			s_pInstance = new MusicManager();
		}
		return s_pInstance;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="isMusic"> true�� ������ �ε�, false�� ȿ������ �ε� </param>
	/// <returns> �����ϸ� true�� ��ȯ </returns>
	bool loadAudio(std::string fileName, std::string id,bool isMusic = false);
	/// <summary>
	/// ȿ���� ���
	/// </summary>
	void playEffectSound(std::string id);
	/// <summary>
	/// ����� ���
	/// </summary>
	/// <param name="type"> PLAY, RESUME, PAUSE, HALT �� �ϳ� ���</param>
	void controlMusic(int type = 0);
	/// <summary>
	/// ����� ����
	/// </summary>
	void clearMusic();
	/// <summary>
	/// ȿ���� ����
	/// </summary>
	/// <param name="id"></param>
	void clearEffectSound(std::string id);
	/// <summary>
	/// ���� ��/�ٿ�
	/// </summary>
	/// <param name="val"></param>
	void changeVolume(int val);
private:
	MusicManager() {}
	static MusicManager* s_pInstance;
	Mix_Music* m_Music = NULL;
	std::map<std::string, Mix_Chunk*> m_musicMap;
	int volume = 5;

};
typedef MusicManager TheMusicManager;
enum SOUND_CONTROL_TYPE {
	PLAY = 0, HALT, PAUSE, RESUME,
};