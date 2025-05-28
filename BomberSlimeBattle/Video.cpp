#include "Video.h"
#include "iostream"

Video* Video::pInstance = NULL;

Video::Video()
{
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    gWindow = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    gRenderer = SDL_CreateRenderer(gWindow, -1, 0);

    font = TTF_OpenFont("Assets/OpenSans-VariableFont_wdth,wght.ttf", 24);
    if (!font) {
        std::cerr << "Error cargando fuente: " << TTF_GetError() << std::endl;
    }
}

Video::~Video()
{
    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
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

    SDL_Texture* texture = nullptr;
    texture = ResourceManager::getInstance()->getGraphicByID(img);

    if (texture != nullptr) {
        SDL_RenderCopy(gRenderer, texture, &rectAux, &r);
    }
    else {
        std::cout << "[Error] renderGraphic: textura con ID " << img << " es NULL." << std::endl;
    }
}

void Video::drawRect(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Rect rect = { x, y, width, height };
    SDL_SetRenderDrawColor(gRenderer, r, g, b, 255);
    SDL_RenderDrawRect(gRenderer, &rect);
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
}

void Video::drawText(const char* text, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    if (!font) {
        return;
    }

    SDL_Color color = { r, g, b };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        std::cerr << "Error renderizando texto: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    if (!texture) {
        std::cerr << "Error creando textura de texto: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = surface->w;
    dst.h = surface->h;

    SDL_RenderCopy(gRenderer, texture, NULL, &dst);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
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
