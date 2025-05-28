#include "Gusano.h"
#include "Astar.h"

void Gusano::colisionBombas(std::vector<Bomb*>& bombas, int val, int xy)
{
    for (auto* bomba : bombas) 
    {
        if (xy == 0) 
        {
            if (gusPos.x + val == bomba->getX() && gusPos.y == bomba->getY()) 
            {
                bomba->setX(val);
            }
        }
        else if (xy == 1) 
        {
            if (gusPos.x == bomba->getX() && gusPos.y + val == bomba->getY()) 
            {
                bomba->setY(val);
            }
        }
    }
}

Gusano::Gusano()
{
	gusId = 0;

	gusSprite.x = 0;
	gusSprite.y = 0;
	gusSprite.h = 0;
	gusSprite.w = 0;

	gusPos.x = 0;
	gusPos.y = 0;

	vel = 0;
}

Gusano::~Gusano()
{
}

void Gusano::init(int tile)
{
	gusSprite.h = tile;
	gusSprite.w = tile;

	gusPos.x = tile * 9;
	gusPos.y = tile * 9;

	vel = tile;
}

void Gusano::loadSprite(std::string file)
{
	gusId = rm->loadAndGetGraphicID(file.c_str());
}

void Gusano::update(const std::vector<int>& map, int mapWidth, int mapHeight, std::pair<int, int> target, bool& objetivoAlcanzado, std::vector<Bomb*>& bombas)
{
    int tileX = gusPos.x / gusSprite.w;
    int tileY = gusPos.y / gusSprite.h;

    if (currentPath.empty() || currentPathIndex >= currentPath.size()) {
        Astar astar(mapWidth, mapHeight, map);
        currentPath = astar.findPath({ tileX, tileY }, target);
        currentPathIndex = 0;
    }

    int now = SDL_GetTicks();
    if (now - lastMoveTime < moveDelay) return;

    auto next = currentPath[currentPathIndex];
    int dirX = next.first - tileX;
    int dirY = next.second - tileY;

    if (dirX == 1 && dirY == 0) //derecha
    {
        colisionBombas(bombas, 32, 0);
    }
    else if (dirX == -1 && dirY == 0) //izquierda
    {
        colisionBombas(bombas, -32, 0);
    }
    else if (dirX == 0 && dirY == 1) //abajo
    {
        colisionBombas(bombas, 32, 1);
    }
    else if (dirX == 0 && dirY == -1) //arriba
    {
        colisionBombas(bombas, -32, 1);
    }

    if (!currentPath.empty() && currentPathIndex < currentPath.size()) {
        auto next = currentPath[currentPathIndex];
        gusPos.x = next.first * gusSprite.w;
        gusPos.y = next.second * gusSprite.h;

        currentPathIndex++;
        lastMoveTime = now;

        if (currentPathIndex >= currentPath.size())
        {
            if (objetivoAlcanzado)
            {
                objetivoAlcanzado = false;
            }
            else
            {
                objetivoAlcanzado = true;
            }
        }
    }
}

void Gusano::render()
{
	vid->renderGraphic(gusId, gusPos.x, gusPos.y, gusSprite.w, gusSprite.h, gusSprite.x, gusSprite.y);
}
