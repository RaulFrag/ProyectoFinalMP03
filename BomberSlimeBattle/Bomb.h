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
    };
    std::vector<Explosion> explosiones;

    ResourceManager* rm = ResourceManager::getInstance();
    Video* vid = Video::getInstance();

    int bombIMG;
    int explosionIMG;

public:
    Bomb(int _x, int _y, int _tileW, int _tileH);

    void update(std::vector<int>& layer3, int mapWidth, int mapHeight);
    void render();
    bool isExplotada() const { return explotada && explosiones.empty(); };
    bool isActiva() const { return activa; };

    const std::vector<Explosion>& getExplosiones() const { return explosiones; };
};
