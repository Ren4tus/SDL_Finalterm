#include "MusicManager.h"
#include <iostream>
MusicManager* MusicManager::s_pInstance = 0;
bool MusicManager::loadAudio(std::string fileName, std::string id, bool isMusic)
{

	if (!isMusic) {
		if (Mix_LoadWAV(fileName.c_str()) != 0) {
			m_musicMap[id] = Mix_LoadWAV(fileName.c_str());
			Mix_VolumeChunk(m_musicMap[id], volume);
			return true;
		}
	}
	else {
		if (Mix_LoadMUS(fileName.c_str()) != 0) {
			m_Music = Mix_LoadMUS(fileName.c_str());
			Mix_VolumeMusic(volume);
			return true;
		}
	}
	return false;
}
void MusicManager::playEffectSound(std::string id)
{
	Mix_PlayChannel(-1, m_musicMap[id], 0);
}
void MusicManager::controlMusic(int type)
{

	switch (type) {
	case PLAY:
		if(Mix_PlayingMusic()==0)
			Mix_PlayMusic(m_Music, -1);
		break;
	case PAUSE:
		if (Mix_PausedMusic() == 0)
			Mix_PauseMusic();
		break;
	case RESUME:
		if (Mix_PausedMusic() == 1)
			Mix_ResumeMusic();
		break;
	case HALT:
		Mix_HaltMusic();
		break;
	default:
		break;
	}
}

void MusicManager::clearMusic()
{
	Mix_FreeMusic(m_Music);
	m_Music = NULL;
}

void MusicManager::clearEffectSound(std::string id)
{

	Mix_FreeChunk(m_musicMap[id]);
	m_musicMap.erase(id);
}

void MusicManager::changeVolume(int val)
{
	(volume + val < 100 && volume + val > 0) ? volume = volume + val : volume = volume;

	//새로 설정된 볼륨을 적용
	for (auto iter = m_musicMap.begin(); iter != m_musicMap.end(); iter++) {
		Mix_VolumeChunk(iter->second, volume);
	}
	Mix_VolumeMusic(volume);

	std::cout << volume << std::endl;
}
