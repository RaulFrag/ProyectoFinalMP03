#pragma once
#include <vector>
#include <map>
#include <string>
#include "SDL_mixer.h"
#include "SDL.h"

class Sound
{
	Sound();
	static Sound* Instance;


public:
	~Sound();
	static Sound* getInstance() {
		if (Instance == nullptr)
		{
			Instance = new Sound();
		}
		return Instance;
	}

	void Init();

	Sint32 loadAndGetAudioID(const char* file);

private:
	Mix_Chunk* LoadSound(const char* file);
	Sint32 addAudio(const char* file);
	void removeAudio(const char* file);
	void removeAllAudio();

	void PlaySound(int ID, int loops);
	void StopSound(int channel);
	
	void SetVolumeSound(int ID, int volume);

	std::vector<Mix_Chunk*> mAudioVector;
	std::map<std::string, Sint32>	mIDAudioMap;
	Uint32				mFirstFreeSlot;
};

