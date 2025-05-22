#pragma once
#include "ResourceManager.h"
#include "Video.h"
#include "Bomb.h"
class Gusano
{
	ResourceManager* rm = ResourceManager::getInstance();
	Video* vid = Video::getInstance();

	SDL_Rect gusPos, gusSprite;
	int gusId;
	int vel;

public:
	Gusano();
	~Gusano();

	void init(int tile);
	void loadSprite(std::string file);
	void update();
	void render();
};

