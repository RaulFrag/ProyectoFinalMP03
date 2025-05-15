#include "Jugador.h"
#include "SDL.h"

Jugador::Jugador()
{
	playerId = 0;

	playerSprite.x = 0;
	playerSprite.y = 0;
	playerSprite.h = 32;
	playerSprite.w = 32;

	playerPos.x = 64;
	playerPos.y = 64;

	vel = 32;
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
		else
		{
			return true;
		}
	}
	else if (xy == 1)
	{

	}
	return false;
}

void Jugador::loadSprite()
{
	playerId = rm->loadAndGetGraphicID("Assets\\slime rosa.png");
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
