#pragma once

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640

#include "ResourceManager.h"

#include <SDL.h>
#include <SDL_ttf.h>

class Video
{
protected:
    Video();
private:
    static Video* pInstance;
    TTF_Font* font;

public:
    ~Video();

    void renderGraphic(int img, int posX, int posY, int width, int height, int spriteX, int spriteY);
    void drawRect(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b);
    void drawText(const char* text, int x, int y, Uint8 r, Uint8 g, Uint8 b);
    void clearScreen(/*unsigned int color_key*/);
    void updateScreen();
    void waitTime(int ms);
    void close();
    static Video* getInstance();

    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
};

