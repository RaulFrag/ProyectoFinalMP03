#include "Jugador.h"
#include "SDL.h"
#include <iostream>

Jugador::Jugador()
{
	playerId = 0;
	playerGraphicID = 0;
	alive = true;

	playerSprite.x = 0;
	playerSprite.y = 0;
	playerSprite.h = 0;
	playerSprite.w = 0;

	playerPos.x = 0;
	playerPos.y = 0;

	vel = 0;
}

Jugador::~Jugador()
{
}

bool Jugador::collision(std::vector<int> Layer2, std::vector<int> Layer3, int val, int xy)
{
	if (xy == 0)
	{
		int i = (playerPos.x + val) / 32 + playerPos.y / 32 * 20;
		if ((Layer2[i] == 0) && (Layer3[i] == 0))
		{
			return false;
		}
	}
	else if (xy == 1)
	{
		int i = playerPos.x / 32 + (playerPos.y + val) / 32 * 20;
		if ((Layer2[i] == 0) && (Layer3[i] == 0))
		{
			return false;
		}
	}
	return true;
}

void Jugador::init(int tile, int id)
{
	playerSprite.h = tile;
	playerSprite.w = tile;
	playerId = id;
	alive = true;
	bombas.clear();

	switch (id)
	{
	case 1:
		playerPos.x = tile * 2;
		playerPos.y = tile * 2;
		break;
	case 2:
		playerPos.x = tile * 17;
		playerPos.y = tile * 17;
		break;
	default:
		break;
	}

	vel = tile;
}

void Jugador::loadSprite(std::string file)
{
	playerId = rm->loadAndGetGraphicID(file.c_str());
}

void Jugador::update(std::vector<int> Layer2, std::vector<int> Layer3, int currentTime)
{
	if (currentTime - lastMoveTime >= moveCooldown)
	{
		if (playerId == 1)
		{
			if (key->getKeyPressed(Ti_Right) == true)
			{
				if (!collision(Layer2, Layer3, vel, 0))
				{
					playerPos.x += vel;
					lastMoveTime = currentTime;
				}
			}
			else if (key->getKeyPressed(Ti_Left) == true)
			{
				if (!collision(Layer2, Layer3, -vel, 0))
				{
					playerPos.x -= vel;
					lastMoveTime = currentTime;
				}
			}
			else if (key->getKeyPressed(Ti_Down) == true)
			{
				if (!collision(Layer2, Layer3, vel, 1))
				{
					playerPos.y += vel;
					lastMoveTime = currentTime;
				}
			}
			else if (key->getKeyPressed(Ti_Up) == true)
			{
				if (!collision(Layer2, Layer3, -vel, 1))
				{
					playerPos.y -= vel;
					lastMoveTime = currentTime;
				}
			}
			else if (key->getKeyPressed(Ti_RShift) == true)
			{
				placeBomb();
			}
		}
		else if (playerId == 2)
		{
			if (key->getKeyPressed(Ti_D) == true)
			{
				if (!collision(Layer2, Layer3, vel, 0))
				{
					playerPos.x += vel;
					lastMoveTime = currentTime;
				}
			}
			else if (key->getKeyPressed(Ti_A) == true)
			{
				if (!collision(Layer2, Layer3, -vel, 0))
				{
					playerPos.x -= vel;
					lastMoveTime = currentTime;
				}
			}
			else if (key->getKeyPressed(Ti_S) == true)
			{
				if (!collision(Layer2, Layer3, vel, 1))
				{
					playerPos.y += vel;
					lastMoveTime = currentTime;
				}
			}
			else if (key->getKeyPressed(Ti_W) == true)
			{
				if (!collision(Layer2, Layer3, -vel, 1))
				{
					playerPos.y -= vel;
					lastMoveTime = currentTime;
				}
			}
			else if (key->getKeyPressed(Ti_F) == true)
			{
				placeBomb();
			}
		}
	}
}

void Jugador::render()
{
	if (alive)
	{
		vid->renderGraphic(playerGraphicID, playerPos.x, playerPos.y, playerSprite.w, playerSprite.h, playerSprite.x, playerSprite.y);
	}
}

void Jugador::checkExplosionCollision(const std::vector<Bomb>& bombas)
{
	for (const auto& bomba : bombas)
	{
		for (const auto& ex : bomba.getExplosiones())
		{
			if (playerPos.x / 32 == ex.x / 32 && playerPos.y / 32 == ex.y / 32)
			{
				alive = false;
				return;
			}
		}
	}
}

void Jugador::placeBomb()
{
	int tileX = (playerPos.x / playerSprite.w) * playerSprite.w;
	int tileY = (playerPos.y / playerSprite.h) * playerSprite.h;

	bombas.emplace_back(tileX, tileY, playerSprite.w, playerSprite.h);
}

void Jugador::updateBombs(std::vector<int>& layer3, int mapWidth, int mapHeight)
{
	for (auto& bomba : bombas)
	{
		bomba.update(layer3, mapWidth, mapHeight);
	}

	bombas.erase(std::remove_if(bombas.begin(), bombas.end(),
		[](Bomb& b) { return b.isExplotada(); }), bombas.end());
}

void Jugador::renderBombs()
{
	for (auto& bomba : bombas)
	{
		bomba.render();
	}
}
