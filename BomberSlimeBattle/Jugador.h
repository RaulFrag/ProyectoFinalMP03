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

	bool collision(std::vector <int> Layer2, std::vector <int> Layer3, int val, int xy);

	void loadSprite();
	void update(std::vector <int> Layer2, std::vector <int> Layer3);
	void render();
};

