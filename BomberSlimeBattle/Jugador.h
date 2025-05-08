#pragma once
#include "ResourceManager.h"
#include "Video.h"

class Jugador
{
	ResourceManager* rm = ResourceManager::getInstance();
	Video* vid = Video::getInstance();
	
	SDL_Rect playerPos, playerSprite;

	int playerId;


public:
	Jugador();
	~Jugador();

	int vel;

	void loadSprite();
	void update();
	void render();
};

