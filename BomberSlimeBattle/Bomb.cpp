#include "Bomb.h"
#include <iostream>

Bomb::Bomb(int _x, int _y, int _tileW, int _tileH)
{
    x = _x / _tileW * _tileH;
    y = _y / _tileW * _tileH;
    tileSize = _tileW;
    tiempo = 100;
    activa = true;
    explotada = false;

    bombIMG = rm->loadAndGetGraphicID("Assets\\bomba.png");
}

void Bomb::update(std::vector<int>& layer3, int mapWidth, int mapHeight)
{
    tiempo--;
    if (tiempo <= 0 && !explotada)
    {
        int cx = x / 32;
        int cy = y / 32;

        int indices[5][2] = {
            {cx, cy},        // Centro
            {cx - 1, cy},    // Izquierda
            {cx + 1, cy},    // Derecha
            {cx, cy - 1},    // Arriba
            {cx, cy + 1}     // Abajo
        };

        for (auto& pos : indices)
        {
            int i = pos[0] + pos[1] * mapWidth;

            if (pos[0] >= 0 && pos[0] < mapWidth && pos[1] >= 0 && pos[1] < mapHeight)
            {
                if (layer3[i] == 19)
                {
                    layer3[i] = 0;
                    std::cout << "Bloque destruida en: " << pos[0] << "," << pos[1] << std::endl;
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
        vid->renderGraphic(bombIMG, x, y, tileSize, tileSize, 0, 0);
    }
}
