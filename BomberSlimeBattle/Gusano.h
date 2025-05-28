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

	std::vector<std::pair<int, int>> currentPath;
	std::pair<int, int> currentTarget;
	int currentPathIndex = 0;
	int lastMoveTime = 0;
	int moveDelay = 1000;

	void colisionBombas(std::vector<Bomb*>& bombas, int val, int xy);

public:
	Gusano();
	~Gusano();

	void init(int tile);
	void loadSprite(std::string file);
	void update(const std::vector<int>& map, int mapWidth, int mapHeight, std::pair<int, int> target, bool& objetivoAlcanzado, std::vector<Bomb*>& bombas);
	void render();
};

