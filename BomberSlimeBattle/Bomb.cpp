#include "Bomb.h"
#include <iostream>

Bomb::Bomb(int _x, int _y, int _tileW, int _tileH)
{
    x = _x / _tileW * _tileH;
    y = _y / _tileW * _tileH;
    tileSize = _tileW;
    tiempo = 3000;
    activa = true;
    explotada = false;

    bombIMG = rm->loadAndGetGraphicID("Assets\\bomba.png");
    explosionIMG = rm->loadAndGetGraphicID("Assets\\slime amarillo.png");
}

void Bomb::update(std::vector<int>& layer3, int mapWidth, int mapHeight)
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
            int i = pos[0] + pos[1] * mapWidth;

            if (pos[0] >= 0 && pos[0] < mapWidth && pos[1] >= 0 && pos[1] < mapHeight) {
                if (layer3[i] == 19) {
                    layer3[i] = 0;
                    std::cout << "Bloque destruido en: " << pos[0] << "," << pos[1] << std::endl;
                }
            }

            Explosion ex;
            ex.x = pos[0] * tileSize;
            ex.y = pos[1] * tileSize;
            ex.tiempoRestante = 3000;
            explosiones.push_back(ex);
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
