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
Highscore hs;

int main(int argc, char* args[])
{

	Mapa* map = new Mapa();

	map->loadMap("Assets\\mapa3.tmx", "Assets\\tileset.png");
	pj1.loadSprite();

	while (true)
	{
		video->clearScreen();

		pj1.update(map->getLayer2(), map->getLayer3());

		map->render();
		pj1.render();

		video->updateScreen();

	}

	//hs.doHighScore();

	return 0;
}