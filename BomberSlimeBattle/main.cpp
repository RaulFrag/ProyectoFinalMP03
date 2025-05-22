#include "iostream"
#include "ResourceManager.h"
#include "Video.h"
#include "mapa.h"
#include "Highscore.h"
#include "Jugador.h"
#include "Thread.h"
#include "Gusano.h"

#define FPS 60
unsigned int lastTime = 0, currentTime, deltaTime;
float msFrame = 1 / (FPS / 1000.0f);


ResourceManager* rm = ResourceManager::getInstance();
Video* video = Video::getInstance();
Input* input = Input::getInstanceI();

Jugador pj1;
Jugador pj2;
Jugador pj3;
Jugador pj4;

Gusano gus;

Highscore hs;
//Mapa* map;

//Thread** myThread = new Thread * ();

/*void Player1(void* _param)
{
	pj1.loadSprite("Assets\\slime naranja.png");
	pj1.init(32, 1);

	while (true)
	{
		pj1.update(map->getLayer2(), map->getLayer3());
	}
}
void Player2(void* _param)
{
	pj2.loadSprite("Assets\\slime verde.png");
	pj2.init(32, 2);

	while (true)
	{
		pj2.update(map->getLayer2(), map->getLayer3());
	}
}
void Player3(void* _param)
{
	pj3.loadSprite("Assets\\slime rosa.png");
	pj3.init(32, 3);

	while (true)
	{
		pj3.update(map->getLayer2(), map->getLayer3());
	}
}
void Player4(void* _param)
{
	pj4.loadSprite("Assets\\slime blanco.png");
	pj4.init(32, 4);

	while (true)
	{
		pj4.update(map->getLayer2(), map->getLayer3());
	}
}*/

int main(int argc, char* args[])
{
	Mapa* map = new Mapa();
	lastTime = SDL_GetTicks();

	//Load Images
	map->loadMap("Assets\\mapa3.tmx", "Assets\\tileset.png");

	pj1.loadSprite("Assets\\slime naranja.png");
	pj2.loadSprite("Assets\\slime verde.png");
	pj3.loadSprite("Assets\\slime rosa.png");
	pj4.loadSprite("Assets\\slime blanco.png");

	gus.loadSprite("Assets\\gusano_izquierda.png");

	pj1.init(32, 1);
	pj2.init(32, 2);
	pj3.init(32, 3);
	pj4.init(32, 4);

	gus.init(32);

	/*myThread[0] = new Thread(Player1);
	myThread[1] = new Thread(Player2);
	myThread[2] = new Thread(Player3);
	myThread[3] = new Thread(Player4);

	myThread[0]->Start((VOID_PTR)1);
	myThread[1]->Start((VOID_PTR)2);
	myThread[2]->Start((VOID_PTR)3);
	myThread[3]->Start((VOID_PTR)4);*/
	
	while (true)
	{
		currentTime = SDL_GetTicks();           // Tiempo actual en ms
		deltaTime = currentTime - lastTime;        // Tiempo que pas� desde el �ltimo frame

		if (deltaTime < msFrame)
		{
			video->waitTime(msFrame - deltaTime);          // Esperar el tiempo restante para mantener la tasa de frames
			currentTime = SDL_GetTicks();                   // Actualizar el tiempo actual despu�s de esperar
		}

		lastTime = currentTime;
		input->UpdateInput();
		
		video->clearScreen();

		//Update Characters
		pj1.update(map->getLayer2(), map->getLayer3(), deltaTime);
		pj2.update(map->getLayer2(), map->getLayer3(), deltaTime);

		//Update Bombs
		pj1.updateBombs(map->getLayer3(), map->getWidth(), map->getHeight());

		//Paint everything
		map->render();
		pj1.render();
		pj2.render();
		pj3.render();
		pj4.render();

		pj1.renderBombs();
		gus.render();

		//Update Screen
		video->updateScreen();
		
	}

	//hs.doHighScore();

	return 0;
}