<<<<<<< Updated upstream
#include "Jugador.h"
#include "SDL.h"

Jugador::Jugador()
{
	playerId = 0;

	playerSprite.x = 0;
	playerSprite.y = 0;
	playerSprite.h = 32;
	playerSprite.w = 32;

	playerPos.x = 0;
	playerPos.y = 0;

	vel = 32;
}

Jugador::~Jugador()
{
}

void Jugador::loadSprite()
{
	playerId = rm->loadAndGetGraphicID("Assets\\slime rosa.png");
}

void Jugador::update()
{
	SDL_Event key_event;
	if (SDL_PollEvent(&key_event)!=0)
	{
		if (playerId == 1)
		{
			switch (key_event.key.type)
			{
			case SDL_KEYDOWN:
				switch (key_event.key.keysym.scancode)
				{
				case SDL_SCANCODE_RIGHT:
					playerPos.x += vel;
					break;
				case SDL_SCANCODE_LEFT:
					playerPos.x -= vel;
					break;
				case SDL_SCANCODE_DOWN:
					playerPos.y += vel;
					break;
				case SDL_SCANCODE_UP:
					playerPos.y -= vel;
					break;
				}
				break;
			default:
				break;
			}
		}
	}
}

void Jugador::render()
{
	vid->renderGraphic(playerId, playerPos.x, playerPos.y, playerSprite.w, playerSprite.h, playerSprite.x, playerSprite.y);
}
=======
#include "Jugador.h"
#include "SDL.h"
#include <iostream>

Jugador::Jugador()
{
	playerId = 0;

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

int Jugador::checkKey()
{
	SDL_Event key_event;
	if (SDL_PollEvent(&key_event) != 0)
	{
		switch (key_event.key.type)
		{
		case SDL_KEYDOWN:
			switch (key_event.key.keysym.scancode)
			{
			case SDL_SCANCODE_RIGHT:
				return 1;
				break;
			case SDL_SCANCODE_LEFT:
				return 2;
				break;
			case SDL_SCANCODE_DOWN:
				return 3;
				break;
			case SDL_SCANCODE_UP:
				return 4;
				break;
			case SDL_SCANCODE_F:
				return 5;
				break;
			case SDL_SCANCODE_D:
				return 6;
				break;
			case SDL_SCANCODE_A:
				return 7;
				break;
			case SDL_SCANCODE_S:
				return 8;
				break;
			case SDL_SCANCODE_W:
				return 9;
				break;
			default:
				return 0;
				break;
			}
			break;
		default:
			return 0;
			break;
		}
	}
	return 0;
}


void Jugador::init(int tile, int id)
{
	playerSprite.h = tile;
	playerSprite.w = tile;

	switch (id)
	{
	case 1:
		playerPos.x = tile * 2;
		playerPos.y = tile * 2;
		break;
	case 2:
		playerPos.x = tile * 17;
		playerPos.y = tile * 2;
		break;
	case 3:
		playerPos.x = tile * 2;
		playerPos.y = tile * 17;
		break;
	case 4:
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

void Jugador::update(std::vector <int> Layer2, std::vector <int> Layer3, int key)
{
	if (playerId == 1)
	{
		switch (key)
		{
		case 1:
			if (!collision(Layer2, Layer3, vel, 0))
			{
				playerPos.x += vel;
			}
			break;
		case 2:
			if (!collision(Layer2, Layer3, -vel, 0))
			{
				playerPos.x -= vel;
			}
			break;
		case 3:
			if (!collision(Layer2, Layer3, vel, 1))
			{
				playerPos.y += vel;
			}
			break;
		case 4:
			if (!collision(Layer2, Layer3, -vel, 1))
			{
				playerPos.y -= vel;
			}
			break;
		case 5:
			placeBomb();
			break;
		}

	}
	else if (playerId == 2)
	{
		if (key != 0)
		{
			std::cout << playerId << ": " << key << std::endl;
		}
		switch (key)
		{
		case 6:
			if (!collision(Layer2, Layer3, vel, 0))
			{
				playerPos.x += vel;
			}
			break;
		case 7:
			if (!collision(Layer2, Layer3, -vel, 0))
			{
				playerPos.x -= vel;
			}
			break;
		case 8:
			if (!collision(Layer2, Layer3, vel, 1))
			{
				playerPos.y += vel;
			}
			break;
		case 9:
			if (!collision(Layer2, Layer3, -vel, 1))
			{
				playerPos.y -= vel;
			}
			break;
		}
	}
}

void Jugador::render()
{
	vid->renderGraphic(playerId, playerPos.x, playerPos.y, playerSprite.w, playerSprite.h, playerSprite.x, playerSprite.y);
}

void Jugador::placeBomb()
{
	bombas.emplace_back(playerPos.x, playerPos.y, playerSprite.w, 90);
}

void Jugador::updateBombs(std::vector<int> layer3, int mapWidth, int mapHeight)
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
>>>>>>> Stashed changes
