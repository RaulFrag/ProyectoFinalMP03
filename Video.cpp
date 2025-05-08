#include "Video.h"

Video* Video::pInstance = NULL;

Video::Video()
{
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    gRenderer = SDL_CreateRenderer(gWindow, -1, 0);
}

Video::~Video()
{
}

void Video::renderGraphic(int img, int posX, int posY, int width, int height, int spriteX, int spriteY)
{
    SDL_Rect r, rectAux;

    r.h = height;
    r.w = width;
    r.x = posX;
    r.y = posY;

    rectAux.h = height;
    rectAux.w = width;
    rectAux.x = spriteX;
    rectAux.y = spriteY;

    SDL_Texture* texture = ResourceManager::getInstance()->getGraphicByID(img);
    SDL_RenderCopy(gRenderer, texture, &rectAux, &r);
}

void Video::clearScreen(/*unsigned int color_key*/)
{
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(gRenderer);
}

void Video::updateScreen()
{
    SDL_RenderPresent(gRenderer);
}

void Video::waitTime(int ms)
{
    SDL_Delay(ms);
}

void Video::close()
{
}

Video* Video::getInstance()
{
    if (pInstance == NULL)
    {
        pInstance = new Video();
    }
    return pInstance;
}
