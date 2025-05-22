#include "Gusano.h"

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

void Gusano::update()
{
}

void Gusano::render()
{
	vid->renderGraphic(gusId, gusPos.x, gusPos.y, gusSprite.w, gusSprite.h, gusSprite.x, gusSprite.y);
}
