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
    explosionIMG = rm->loadAndGetGraphicID("Assets\\slime amarillo.png");
}

void Bomb::update(std::vector<int>& layer3, int mapWidth, int mapHeight, const std::vector<int>& layer2)
{
    tiempo--;
    if (tiempo <= 0 && !explotada) {
        int cx = x / tileSize;
        int cy = y / tileSize;

        int indices[5][2] = {
            {cx, cy},        // Centro
            {cx - 1, cy},    // Izquierda
            {cx + 1, cy},    // Derecha
            {cx, cy - 1},    // Arriba
            {cx, cy + 1}     // Abajo
        };

        for (auto& pos : indices) {
            int tx = pos[0];
            int ty = pos[1];

            if (tx >= 0 && tx < mapWidth && ty >= 0 && ty < mapHeight) {
                int i = tx + ty * mapWidth;

                if (layer2[i] != 0) {
                    continue;
                }

                if (layer3[i] != 0) {
                    layer3[i] = 0;
                    std::cout << "Bloque destruido en: " << tx << "," << ty << std::endl;
                }

                Explosion ex;
                ex.x = tx * tileSize;
                ex.y = ty * tileSize;
                ex.tiempoRestante = 30;
                explosiones.push_back(ex);
            }
        }

        explotada = true;
        activa = false;
    }

    for (auto& ex : explosiones) {
        ex.tiempoRestante--;
    }

    explosiones.erase(
        std::remove_if(explosiones.begin(), explosiones.end(),
            [](const Explosion& e) { return e.tiempoRestante <= 0; }),
        explosiones.end()
    );
}

void Bomb::render()
{
    if (activa && !explotada)
    {
        vid->renderGraphic(bombIMG, x, y, tileSize, tileSize, 0, 0);
    }


    for (auto& ex : explosiones)
    {
        vid->renderGraphic(explosionIMG, ex.x, ex.y, tileSize, tileSize, 0, 0);
    }
}
