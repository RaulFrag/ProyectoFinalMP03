#include "Bomb.h"
#include <iostream>

Bomb::Bomb(int _x, int _y, int _tileSize, int tiempoInicial)
{
    x = _x / _tileSize * _tileSize;
    y = _y / _tileSize * _tileSize;
    tileSize = _tileSize;
    tiempo = tiempoInicial;
    activa = true;
    explotada = false;

    bombaId = rm->loadAndGetGraphicID("bomba.png");
}

void Bomb::update(std::vector<int>& layer3, int mapWidth, int mapHeight)
{
    if (!activa) return;

    tiempo--;
    if (tiempo <= 0 && !explotada)
    {
        int cx = x / tileSize;
        int cy = y / tileSize;

        int indices[5][2] = {
            {cx, cy}, {cx - 1, cy}, {cx + 1, cy}, {cx, cy - 1}, {cx, cy + 1}
        };

        for (auto& pos : indices)
        {
            int i = pos[0] + pos[1] * mapWidth;

            if (pos[0] >= 0 && pos[0] < mapWidth && pos[1] >= 0 && pos[1] < mapHeight)
            {
                if (layer3[i] != 0)
                {
                    layer3[i] = 0;
                    std::cout << "Destruido en: " << pos[0] << "," << pos[1] << std::endl;
                }
            }
        }

        explotada = true;
        activa = false;
    }
}

void Bomb::render()
{
    if (activa && !explotada)
    {
        vid->renderGraphic(bombaId, x, y, tileSize, tileSize, 0, 0);
    }
}
