#pragma once
#include "ResourceManager.h"
#include "Video.h"
#include "Bomb.h"
#include "Input.h"

class Jugador
{
	ResourceManager* rm = ResourceManager::getInstance();
	Video* vid = Video::getInstance();
	Input* key = Input::getInstanceI();
	
	SDL_Rect playerPos, playerSprite;

	int playerGraphicID;
	int playerId;
	bool alive;
	int vel;

	int lastMoveTime = 0;
	int moveCooldown = 150;

	bool collision(std::vector <int> Layer2, std::vector <int> Layer3, int val, int xy);
	bool collisionBombas(int val, int xy);

	std::vector<Bomb> bombas;

public:
	Jugador();
	~Jugador();

	void init(int tile, int id);
	void loadSprite(std::string file);
	void update(std::vector <int> Layer2, std::vector <int> Layer3, int currentTime);
	void render();

	void checkExplosionCollision(const std::vector<Bomb>& bombas);
	bool isAlive() const { return alive; };

	void placeBomb();
	void updateBombs(std::vector<int>& layer3, int mapWidth, int mapHeight, std::vector<int>& layer2);
	void renderBombs();
	const std::vector<Bomb>& getBombas() const { return bombas; };

	std::pair<int, int> getTilePos() const { return { playerPos.x / 32, playerPos.y / 32 }; }
};
