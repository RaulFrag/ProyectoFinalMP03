#include "Sound.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "iostream"

Sound* Sound::Instance = nullptr;

Sound::Sound()
{
	mAudioVector = {};
	mIDAudioMap.clear();
	mFirstFreeSlot = 0;
}

Sound::~Sound()
{
}

void Sound::Init()
{
	SDL_InitSubSystem(SDL_INIT_AUDIO);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_AllocateChannels(128);
}

Sint32 Sound::loadAndGetAudioID(const char* file)
{
	std::map<std::string, Sint32>::iterator it = mIDAudioMap.find(file);
	if (mIDAudioMap.find(file) == mIDAudioMap.end())
	{
		int re = addAudio(file);
		if (re != -1)
		{
			mIDAudioMap.insert(std::pair<std::string, Sint32>(file, re));
		}
		return re;
	}
	return it->second;
}

Mix_Chunk* Sound::LoadSound(const char* file)
{
	Mix_Chunk* sound = Mix_LoadWAV(file);
	if (sound)
	{
		return sound;
	}
	std::cout << "Sound could not be loaded! [SDL Error]: " << Mix_GetError() << std::endl;
	return nullptr;
}

Sint32 Sound::addAudio(const char* file)
{
	Mix_Chunk* sound = Mix_LoadWAV(file);

	if (sound == NULL)
	{
		std::cout << SDL_GetError();
		return -1;
	}
	else
	{
		mAudioVector.push_back(sound);
		return mAudioVector.size() - 1;
	}
}

void Sound::removeAudio(const char* file)
{
	std::map<std::string, Sint32>::iterator it = mIDAudioMap.find(file);
	if (it != mIDAudioMap.end())
	{
		Mix_FreeChunk(mAudioVector[it->second]);
		mAudioVector[it->second] = nullptr;
		mIDAudioMap.erase(it);
	}
}
