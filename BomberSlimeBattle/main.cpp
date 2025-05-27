#include "iostream"
#include "ResourceManager.h"
#include "Video.h"
#include "mapa.h"
#include "Highscore.h"
#include "Jugador.h"
#include "Input.h"
#include "Gusano.h"
#include "Menu.h"

#define FPS 60
unsigned int lastTime = 0, currentTime, deltaTime;
float msFrame = 1 / (FPS / 1000.0f);


ResourceManager* rm = ResourceManager::getInstance();
Video* video = Video::getInstance();
Input* input = Input::getInstanceI();

Menu menu;
Jugador pj1;
Jugador pj2;

Gusano gusano;

Highscore hs;


int main(int argc, char* args[])
{
	Mapa* map = new Mapa();
	
	int mapIndex = 0;
	
	//Load Images
	pj1.loadSprite("Assets\\slime naranja.png");
	pj2.loadSprite("Assets\\slime verde.png");
	gusano.loadSprite("Assets\\gusano_izquierda.png");

	
	bool gameOver = false;
	int currentMap = 1;
	int gamestate = 0;
	bool exitgame = false;
	while (!exitgame)
	{
		currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastTime;

		if (deltaTime < msFrame)
		{
			video->waitTime(msFrame - deltaTime);
			currentTime = SDL_GetTicks();
		}

		lastTime = currentTime;
		input->UpdateInput();

		video->clearScreen();
		

		// -- Menu
		if (gamestate == 0) {
			SDL_Event e;
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					exitgame = true;
				}
				else if (e.type == SDL_KEYDOWN) {
					switch (e.key.keysym.sym) {
					case SDLK_UP:
						menu.update(SDLK_UP);
						break;
					case SDLK_DOWN:
						menu.update(SDLK_DOWN);
						break;
					case SDLK_RETURN: {
						int option = menu.getSelectedOption();
						if (option == 1) {
							std::string mapPath = "Assets/mapa" + std::to_string(currentMap) + ".tmx";
							map->loadMap(mapPath.c_str(), "Assets/tileset.png");
							gamestate = 1;
							menu.resetSelection();
							pj1.init(32, 1);
							pj2.init(32, 2);
							gameOver = false;
						}
						else if (option == 2) {
							currentMap = (currentMap % 3) + 1;
							menu.resetSelection();
							menu.setCurrentMap(currentMap);
						}
						else if (option == 3) {
							exitgame = true;
						}
						break;
					}
					}
				}
			}
			menu.render();
		}
		// -- Juego
		if (gamestate == 1)
		{
			std::cout << "Cambiando gamestate a 1 (Juego)" << std::endl;
			//Update Characters
			pj1.update(map->getLayer2(), map->getLayer3(), currentTime);
			pj2.update(map->getLayer2(), map->getLayer3(), currentTime);

			//Update AI
			gusano.update(map->getLayer2(), 20, 20, pj1.getTilePos());

			//Update Bombs
			pj1.updateBombs(map->getLayer3(), map->getWidth(), map->getHeight());
			pj2.updateBombs(map->getLayer3(), map->getWidth(), map->getHeight());
			
			pj1.checkExplosionCollision(pj1.getBombas());
			pj1.checkExplosionCollision(pj2.getBombas());
			pj2.checkExplosionCollision(pj1.getBombas());
			pj2.checkExplosionCollision(pj2.getBombas());

			if ((!pj1.isAlive() || !pj2.isAlive()) && !gameOver) 
			{
				gameOver = true;
				gamestate = 2;
			}

			//Paint everything
			map->render();
			pj1.render();
			pj2.render();
			pj1.renderBombs();
			pj2.renderBombs();

			gusano.render();

		}
		// -- HighScore
		if (gamestate == 2)
		{
			gamestate = 0;
		}

		//Update Screen
		video->updateScreen();
	}

	//hs.doHighScore();

	return 0;
}