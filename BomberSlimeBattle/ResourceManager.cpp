#include "ResourceManager.h"
#include "iostream"
#include "SDL_image.h"
#include "Video.h"

ResourceManager* ResourceManager::pInstance = NULL;

ResourceManager::~ResourceManager()
{
}

void ResourceManager::removeGraphic(const char* file)
{
	std::map<std::string, Sint32>::iterator it = mIDGraphicMap.find(file);
	if (it != mIDGraphicMap.end())
	{
		SDL_DestroyTexture(mGraphicsVector[it->second]);
		mGraphicsVector[it->second] = nullptr;
		mIDGraphicMap.erase(it);
	}
}

Sint32 ResourceManager::loadAndGetGraphicID(const char* file)
{
	std::map<std::string, Sint32>::iterator it = mIDGraphicMap.find(file);
	if (mIDGraphicMap.find(file) == mIDGraphicMap.end())
	{
		int re = addGraphic(file);
		if (re != -1)
		{
			mIDGraphicMap.insert(std::pair<std::string, Sint32>(file, re));
		}
		return re;
	}
	return it->second;
}

std::string ResourceManager::getGraphicPathByID(Sint32 ID)
{
	for (auto i = mIDGraphicMap.begin(); i != mIDGraphicMap.end(); i++)
	{
		if (i->second == ID)
		{
			return i->first;
		}
	}
	return "NULL";
}

void ResourceManager::getGraphicSize(Sint32 img, int& width, int& height)
{
	if ((img >= 0) && (img <= mGraphicsVector.size() - 1))
	{
		SDL_QueryTexture(mGraphicsVector[img], NULL, NULL, &width, &height);
	}
}

Uint16 ResourceManager::getGraphicWidth(Sint32 img)
{
	int w;
	SDL_QueryTexture(mGraphicsVector[img], NULL, NULL, &w, NULL);
	return w;
}

Uint16 ResourceManager::getGraphicHeight(Sint32 img)
{
	int h;
	SDL_QueryTexture(mGraphicsVector[img], NULL, NULL, NULL, &h);
	return h;
}

SDL_Texture* ResourceManager::getGraphicByID(Sint32 ID)
{
	if ((ID >= 0) && (ID <= mGraphicsVector.size() - 1))
	{
		return mGraphicsVector[ID];
	}
}

void ResourceManager::setAlphaGraphic(Sint32 ID, Uint8 alpha_value)
{
	SDL_SetTextureAlphaMod(mGraphicsVector[ID], alpha_value);
}

void ResourceManager::printLoadedGraphics()
{
	for (auto it = mIDGraphicMap.begin(); it != mIDGraphicMap.end(); it++)
	{
		std::cout << it->first << std::endl;
	}
}

Sint32 ResourceManager::createGraphic(const char* name, Uint16 width, Uint16 height)
{
	return Sint32();
}

ResourceManager* ResourceManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new ResourceManager();
	}
	return pInstance;
}

ResourceManager::ResourceManager()
{
	mGraphicsVector = {};
	mIDGraphicMap.clear();
	mFirstFreeSlot = 0;
}

Sint32 ResourceManager::addGraphic(const char* file)
{
	Video* video = Video::getInstance();
	SDL_Surface* img = IMG_Load(file);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(video->gRenderer, img);

	SDL_FreeSurface(img);

	if (img == NULL)
	{
		std::cout << SDL_GetError();
		return -1;
	}
	if (texture == nullptr) {
		std::cout << "SDL_CreateTextureFromSurface error: " << SDL_GetError() << std::endl;
		return -1;
	}

	Uint32 index = updateFirstFreeSlotGraphic();

	if (index < mGraphicsVector.size()) {
		mGraphicsVector[index] = texture;
	}
	else
	{
		mGraphicsVector.push_back(texture);
		return mGraphicsVector.size()-1;
	}
}

Uint32 ResourceManager::updateFirstFreeSlotGraphic()
{
	for (Uint32 i = 0; i < mGraphicsVector.size(); ++i) {
		if (mGraphicsVector[i] == nullptr) {
			return i;
		}
	}
	return mGraphicsVector.size();
}
