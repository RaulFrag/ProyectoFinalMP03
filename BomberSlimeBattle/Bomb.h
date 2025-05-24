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

    ResourceManager* rm = ResourceManager::getInstance();
    Video* vid = Video::getInstance();

    int bombIMG;

public:
    Bomb(int _x, int _y, int _tileW, int _tileH);

    void update(std::vector<int>& layer3, int mapWidth, int mapHeight);
    void render();
    bool isExplotada() const { return explotada; }
    bool isActiva() const { return activa; }
};
