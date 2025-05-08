#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

void Input::InitInput()
{
	for (size_t i = 0; i < Ti_Size; i++)
	{
		teclas[i] = false;
	}
	eje.x = 0;
	eje.y = 0;
	endGame = false;
}

Sint16 Input::getEjeX()
{
	return eje.x;
}

Sint16 Input::getEjeY()
{
	return eje.y;
}

bool Input::getEndGame()
{
	return endGame;
}

bool Input::getKeyPressed(Ti_Keys key)
{
	return teclas[key];
}

void Input::UpdateInput()
{
	SDL_Event test_event;
	while (SDL_PollEvent(&test_event)) {
		switch (test_event.type) {
		case SDL_QUIT:
			endGame = true;
			break;
		case SDL_CONTROLLERAXISMOTION:
			if (test_event.caxis.axis == 0)
			{
				eje.x = test_event.caxis.value;
			}
			if (test_event.caxis.axis == 1)
			{
				eje.y = test_event.caxis.value;
			}
			break;
		case SDL_KEYDOWN:
			teclas[test_event.key.keysym.scancode] = true; 
			break;
		case SDL_KEYUP:
			teclas[test_event.key.keysym.scancode] = false;
			break;
		default:
			break;
		}
	}
}

Input* Input::getInstanceI()
{
	if (pInstanceI == NULL)
	{
		pInstanceI = new Input();
	}
	return pInstanceI;
}
