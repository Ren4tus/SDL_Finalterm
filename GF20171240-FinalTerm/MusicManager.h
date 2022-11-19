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
	/// <param name="isMusic"> true면 음악을 로드, false면 효과음을 로드 </param>
	/// <returns> 성공하면 true를 반환 </returns>
	bool loadAudio(std::string fileName, std::string id,bool isMusic = false);
	/// <summary>
	/// 효과음 재생
	/// </summary>
	void playEffectSound(std::string id);
	/// <summary>
	/// 배경음 재생
	/// </summary>
	/// <param name="type"> PLAY, RESUME, PAUSE, HALT 중 하나 사용</param>
	void controlMusic(int type = 0);
	/// <summary>
	/// 배경음 제거
	/// </summary>
	void clearMusic();
	/// <summary>
	/// 효과음 제거
	/// </summary>
	/// <param name="id"></param>
	void clearEffectSound(std::string id);
	/// <summary>
	/// 볼륨 업/다운
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