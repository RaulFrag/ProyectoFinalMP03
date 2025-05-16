#include "Jugador.h"
#include "SDL.h"

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

void Jugador::update(std::vector <int> Layer2, std::vector <int> Layer3)
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
					if (!collision(Layer2, Layer3, vel, 0))
					{
						playerPos.x += vel;
					}
					break;
				case SDL_SCANCODE_LEFT:
					if (!collision(Layer2, Layer3, -vel, 0))
					{
						playerPos.x -= vel;
					}
					break;
				case SDL_SCANCODE_DOWN:
					if (!collision(Layer2, Layer3, vel, 1))
					{
						playerPos.y += vel;
					}
					break;
				case SDL_SCANCODE_UP:
					if (!collision(Layer2, Layer3, -vel, 1))
					{
						playerPos.y -= vel;
					}
					break;
				}
				break;
			default:
				break;
			}
		}
		else if (playerId == 2)
		{
			switch (key_event.key.type)
			{
			case SDL_KEYDOWN:
				switch (key_event.key.keysym.scancode)
				{
				case SDL_SCANCODE_D:
				if (!collision(Layer2, Layer3, vel, 0))
					{
						playerPos.x += vel;
					}
					break;
				case SDL_SCANCODE_A:
					if (!collision(Layer2, Layer3, -vel, 0))
					{
						playerPos.x -= vel;
					}
					break;
				case SDL_SCANCODE_S:
					if (!collision(Layer2, Layer3, vel, 1))
					{
						playerPos.y += vel;
					}
					break;
				case SDL_SCANCODE_W:
					if (!collision(Layer2, Layer3, -vel, 1))
					{
						playerPos.y -= vel;
					}
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
