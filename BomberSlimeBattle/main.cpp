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
Highscore hs;


int main(int argc, char* args[])
{
	Mapa* map = new Mapa();

	//Load Images
	
	map->loadMap("Assets\\mapa1.tmx", "Assets\\tileset.png");

	pj1.loadSprite("Assets\\slime naranja.png");
	pj2.loadSprite("Assets\\slime verde.png");

	
	int playersAlive = 0;
	int gamestate = 0;
	bool exitgame = false;
	while (!exitgame)
	{
		video->clearScreen();

		if (gamestate == 0)
		{
			pj1.init(32, 1);
			pj2.init(32, 2);
			gamestate = 1;
		}
		if (gamestate == 1)
		{
			playersAlive = 2;


			//Update Characters
			int key = pj1.checkKey();
			pj1.update(map->getLayer2(), map->getLayer3(), key);
			pj2.update(map->getLayer2(), map->getLayer3(), key);

			//Update Bombs
			pj1.updateBombs(map->getLayer3(), map->getWidth(), map->getHeight());
			pj2.updateBombs(map->getLayer3(), map->getWidth(), map->getHeight());

			//Paint everything
			map->render();
			pj1.render();
			pj2.render();
			pj1.renderBombs();
			pj2.renderBombs();

		}
		if (gamestate == 2)
		{

		}

		//Update Screen
		video->updateScreen();

	}

	//hs.doHighScore();

	return 0;
}