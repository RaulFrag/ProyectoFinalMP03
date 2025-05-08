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
}

Jugador::~Jugador()
{
}

void Jugador::loadSprite()
{
	playerId = rm->loadAndGetGraphicID("Assets\\slime rosa.png");
}

void Jugador::playerMovement()
{
	SDL_Event key_event;
	if (SDL_PollEvent(&key_event)!=0)
	{
		switch (key_event.key.type)
		{
		case SDL_KEYDOWN:
			switch (key_event.key.keysym.scancode)
			{
			case 79:
				playerPos.x += 5;
				break;
			case 80:
				playerPos.x -= 5;
				break;
			}
			break;
		default:
			break;
		}
	}

	vid->renderGraphic(playerId, playerPos.x, playerPos.y, playerSprite.w, playerSprite.h, playerSprite.x, playerSprite.y);
}
