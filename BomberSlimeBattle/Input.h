#pragma once
#include "SDL.h"

enum Key_State
{

};
enum Ti_Keys
{
	Ti_Space = SDL_SCANCODE_SPACE,
	Ti_Enter = SDL_SCANCODE_RETURN,
	Ti_Shift = SDL_SCANCODE_LSHIFT,
	Ti_Control = SDL_SCANCODE_LCTRL,
	Ti_Borrar = SDL_SCANCODE_BACKSPACE,
	Ti_Tab = SDL_SCANCODE_TAB,
	Ti_Alt = SDL_SCANCODE_LALT,
	Ti_Esc = SDL_SCANCODE_ESCAPE,
	Ti_Right = SDL_SCANCODE_RIGHT,
	Ti_Left,
	Ti_Down,
	Ti_Up,
	Ti_1 = SDL_SCANCODE_1,
	Ti_2,
	Ti_3,
	Ti_4,
	Ti_5,
	Ti_6,
	Ti_7,
	Ti_8,
	Ti_9,
	Ti_0,
	Ti_A = SDL_SCANCODE_A,
	Ti_B,
	Ti_C,
	Ti_D,
	Ti_E,
	Ti_F,
	Ti_G,
	Ti_H,
	Ti_I,
	Ti_J,
	Ti_K,
	Ti_L,
	Ti_M,
	Ti_N,
	Ti_O,
	Ti_P,
	Ti_Q,
	Ti_R,
	Ti_S,
	Ti_T,
	Ti_U,
	Ti_V,
	Ti_W,
	Ti_X,
	Ti_Y,
	Ti_Z,
	Ti_Size = 256
};

class Input
{
	struct joystick
	{
		Sint16 x;
		Sint16 y;
	};
	bool endGame;
	joystick eje;
	bool teclas[Ti_Size];

	static Input* pInstanceI;

protected:

	Input();

public:

	~Input();

	void InitInput();

	Sint16 getEjeX();
	Sint16 getEjeY();

	bool getEndGame();

	bool getKeyPressed(Ti_Keys key);

	void UpdateInput();

	static Input* getInstanceI();
};

