#pragma once
#include "ResourceManager.h"
#include "Video.h"
#include "Bomb.h"

class Jugador
{
	ResourceManager* rm = ResourceManager::getInstance();
	Video* vid = Video::getInstance();
	
	SDL_Rect playerPos, playerSprite;

	int playerId;

	bool collision(std::vector <int> Layer2, std::vector <int> Layer3, int val, int xy);

	std::vector<Bomb> bombas;

public:
	Jugador();
	~Jugador();

	int vel;

	int checkKey();

	void init(int tile, int id);
	void loadSprite(std::string file);
	void update(std::vector <int> Layer2, std::vector <int> Layer3, int key);
	void render();

	void placeBomb();
	void updateBombs(std::vector<int> layer3, int mapWidth, int mapHeight);
	void renderBombs();
};
