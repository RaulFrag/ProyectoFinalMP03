#include "Jugador.h"
#include "SDL.h"

Jugador::Jugador()
{
	playerId = 0;

	playerSprite.x = 0;
	playerSprite.y = 0;
	playerSprite.h = 16;
	playerSprite.w = 16;

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
