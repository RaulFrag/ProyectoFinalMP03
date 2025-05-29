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
	
	static Uint32 deathTime = 0;

	int lastMenuUpdate = 0;
	int menuCooldown = 200;
	int mapIndex = 0;

	//Load Images
	pj1.loadSprite("Assets\\slime naranja.png");
	pj2.loadSprite("Assets\\slime verde.png");
	gusano.loadSprite("Assets\\gusano_izquierda.png");

	bool gameOver = false;
	int currentMap = 1;
	int gamestate = 0;
	bool exitgame = false;
	int counter = 0;

	bool changePlayer = false;
	bool replay = false;

	while (!exitgame)
	{
		if (replay && currentTime - lastMenuUpdate >= menuCooldown)
		{
			counter++;
			if (counter == 20)
			{
				replay = false;
				counter = 0;
			}
		}
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
			if (input->getKeyPressed(Ti_Esc) == true)
			{
				exitgame = true;
			}
			else if (currentTime - lastMenuUpdate >= menuCooldown)
			{
				if (!replay)
				{
					if (input->getKeyPressed(Ti_Up) == true)
					{
						menu.update(SDLK_UP);
						lastMenuUpdate = currentTime;
					}
					else if (input->getKeyPressed(Ti_Down) == true)
					{
						menu.update(SDLK_DOWN);
						lastMenuUpdate = currentTime;
					}
					else if (input->getKeyPressed(Ti_Enter) == true)
					{
						int option = menu.getSelectedOption();
						if (option == 1) {
							std::string mapPath = "Assets/mapa" + std::to_string(currentMap) + ".tmx";
							map->loadMap(mapPath.c_str(), "Assets/tileset.png");
							gamestate = 1;
							menu.resetSelection();
							pj1.init(32, 1);
							pj2.init(32, 2);
							gusano.init(32);
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
						lastMenuUpdate = currentTime;
					}
				}
			}
			menu.render();
		}
		// -- Juego
		if (gamestate == 1)
		{
			//Update Characters
			if (!gameOver)
			{
				pj1.update(map->getLayer2(), map->getLayer3(), currentTime);
				pj2.update(map->getLayer2(), map->getLayer3(), currentTime);
			}

			//Update AI
			std::vector<Bomb*> bombas;

			for (auto& b : pj1.getBombas()) {
				bombas.push_back(&b);
			}
			for (auto& b : pj2.getBombas()) {
				bombas.push_back(&b);
			}

			if (!gameOver)
			{
				if (!changePlayer)
				{
					gusano.update(map->getLayer2(), 20, 20, pj1.getTilePos(), changePlayer, bombas);
				}
				else
				{
					gusano.update(map->getLayer2(), 20, 20, pj2.getTilePos(), changePlayer, bombas);
				}
			}

			//Update Bombs
			pj1.updateBombs(map->getLayer3(), map->getWidth(), map->getHeight(), map->getLayer2());
			pj2.updateBombs(map->getLayer3(), map->getWidth(), map->getHeight(), map->getLayer2());
			
			pj1.checkExplosionCollision(pj1.getBombas());
			pj1.checkExplosionCollision(pj2.getBombas());
			pj2.checkExplosionCollision(pj1.getBombas());
			pj2.checkExplosionCollision(pj2.getBombas());

			if ((!pj1.isAlive() || !pj2.isAlive()) && !gameOver)
			{
				gameOver = true;
				deathTime = SDL_GetTicks();
			}

			if (gameOver && SDL_GetTicks() - deathTime >= 3000)
			{
				gamestate = 2;
				gusano.~Gusano();

				if (!pj1.isAlive())
				{
					hs.doHighScore("2");
				}
				else if (!pj2.isAlive())
				{
					hs.doHighScore("1");
				}
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
			std::vector<std::pair<std::string, UINT_32>> scores = hs.getScores();

			video->drawText("HIGHSCORES", 200, 50, 255, 255, 0);

			int y = 100;
			for (const auto& entry : scores)
			{
				std::string line = entry.first + " : " + std::to_string(entry.second);
				video->drawText(line.c_str(), 180, y, 255, 255, 255);
				y += 30;
			}

			video->drawText("Presiona ENTER para volver al menu", 130, y + 50, 200, 200, 200);

			if (currentTime - lastMenuUpdate >= menuCooldown)
			{
				if (input->getKeyPressed(Ti_Enter) == true)
				{
					gamestate = 0;
					replay = true;
				}
			}
		}

		//Update Screen
		video->updateScreen();
	}

	video->~Video();
	delete map;
	return 0;
}
