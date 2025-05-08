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

	void loadSprite();
	void playerMovement();
};

