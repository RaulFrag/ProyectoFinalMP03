#include "iostream"
#include "ResourceManager.h"
#include "Video.h"
#include "mapa.h"
#include "Highscore.h"
#include "Jugador.h"
#include "Thread.h"

#define FPS 60
unsigned int lastTime = 0, currentTime, deltaTime;
float msFrame = 1 / (FPS / 1000.0f);


ResourceManager* rm = ResourceManager::getInstance();
Video* video = Video::getInstance();

Jugador pj1;
Jugador pj2;
Jugador pj3;
Jugador pj4;
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

	//Load Images
	map->loadMap("Assets\\mapa3.tmx", "Assets\\tileset.png");

	pj1.loadSprite("Assets\\slime naranja.png");
	pj2.loadSprite("Assets\\slime verde.png");
	pj3.loadSprite("Assets\\slime rosa.png");
	pj4.loadSprite("Assets\\slime blanco.png");

	pj1.init(32, 1);
	pj2.init(32, 2);
	pj3.init(32, 3);
	pj4.init(32, 4);

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
		video->clearScreen();

		//Update Characters
		int key = pj1.checkKey();
		pj1.update(map->getLayer2(), map->getLayer3(), key);
		pj2.update(map->getLayer2(), map->getLayer3(), key);
		int p3 = pj1.checkKey();
		pj3.update(map->getLayer2(), map->getLayer3(), p3);
		int p4 = pj1.checkKey();
		pj4.update(map->getLayer2(), map->getLayer3(), p4);

		//Update Bombs
		pj1.updateBombs(map->getLayer3(), map->getWidth(), map->getHeight());

		//Paint everything
		map->render();
		pj1.render();
		pj2.render();
		pj3.render();
		pj4.render();

		//Update Screen
		video->updateScreen();

	}

	//hs.doHighScore();

	return 0;
}