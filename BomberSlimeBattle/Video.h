#pragma once

#define SCREEN_WIDTH 920
#define SCREEN_HEIGHT 820

#include "ResourceManager.h"

class Video
{
protected:
    Video();
private:
    static Video* pInstance;

public:
    ~Video();

    void renderGraphic(int img, int posX, int posY, int width, int height, int spriteX, int spriteY);
    void clearScreen(/*unsigned int color_key*/);
    void updateScreen();
    void waitTime(int ms);
    void close();
    static Video* getInstance();

    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
};

