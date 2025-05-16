#include "iostream"
#include "ResourceManager.h"
#include "Video.h"
#include "mapa.h"
#include "Highscore.h"
#include "Jugador.h"

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

int main(int argc, char* args[])
{
	Mapa* map = new Mapa();
	//Load Images
	map->loadMap("Assets\\mapa3.tmx", "Assets\\tileset.png");
	pj1.loadSprite("Assets\\slime naranja.png");
	pj2.loadSprite("Assets\\slime verde.png");
	pj3.loadSprite("Assets\\slime rosa.png");
	pj4.loadSprite("Assets\\slime blanco.png");

	//Load Characters
	pj1.init(32, 1);
	pj2.init(32, 2);
	pj3.init(32, 3);
	pj4.init(32, 4);
	while (true)
	{
		video->clearScreen();

		//Update Characters
		pj1.update(map->getLayer2(), map->getLayer3());
		pj2.update(map->getLayer2(), map->getLayer3());
		pj3.update(map->getLayer2(), map->getLayer3());
		pj4.update(map->getLayer2(), map->getLayer3());

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