#pragma once

#include <vector>
#include "ResourceManager.h"
#include "Video.h"

class Bomb
{
private:
    int x, y;
    int tileSize;
    int tiempo;
    bool activa;
    bool explotada;

    struct Explosion {
        int x, y;
        int tiempoRestante;
        int frame;
        int frameCounter;
        static const int maxFrames = 64;
        static const int frameDuration = 2;

        Explosion(int _x, int _y, int _tiempoRestante) : x(_x), y(_y), tiempoRestante(_tiempoRestante), frame(0), frameCounter(0) { }
    };
    std::vector<Explosion> explosiones;

    static const int frameWidth = 128;
    static const int frameHeight = 128;
    static const int spriteSheetColumns = 8;

    ResourceManager* rm = ResourceManager::getInstance();
    Video* vid = Video::getInstance();

    int bombIMG;
    int explosionIMG;

public:
    Bomb(int _x, int _y, int _tileW, int _tileH);

    void update(std::vector<int>& layer3, int mapWidth, int mapHeight, const std::vector<int>& layer2);
    void render();
    bool isExplotada() const { return explotada && explosiones.empty(); };
    bool isActiva() const { return activa; };

    const std::vector<Explosion>& getExplosiones() const { return explosiones; };
};
