#include "Gusano.h"
#include "Astar.h"

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

void Gusano::update(const std::vector<int>& map, int mapWidth, int mapHeight, std::pair<int, int> target)
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

    if (!currentPath.empty() && currentPathIndex < currentPath.size()) {
        auto next = currentPath[currentPathIndex];
        gusPos.x = next.first * gusSprite.w;
        gusPos.y = next.second * gusSprite.h;

        currentPathIndex++;
        lastMoveTime = now;
    }
}

void Gusano::render()
{
	vid->renderGraphic(gusId, gusPos.x, gusPos.y, gusSprite.w, gusSprite.h, gusSprite.x, gusSprite.y);
}
