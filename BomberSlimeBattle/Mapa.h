#pragma once

#include <vector>
#include "Tiles.h"
#include "ResourceManager.h"
#include "Video.h"

const int NUM_CAPAS = 3;

class Mapa
{
	int _width;
	int _height;
	int _tileWidth;
	int _tileHeight;
	int tilemap;
	
	std::vector <int> Layers[NUM_CAPAS];
	std::vector <int> Layers1[NUM_CAPAS];

	Tiles _tiles;
	ResourceManager* rm = ResourceManager::getInstance();
	Video* vid = Video::getInstance();

	int _CameraX;

public:
	Mapa();
	~Mapa();

	int loadMap(const char* filename, const char* imagename);

	void render();

	int getWidth() { return _width; };
	int getTileWidth() { return _tileWidth; };
	int getHeight() { return _height; };
	int getTileHeight() { return _tileHeight; };

	int getIDfromLayer(int layer, int PosX, int PosY);

	void saveBinary();
	void readBinary(const char* filename);

	void setRenderInitX(int value) { _CameraX = value; };

	std::vector <int>& getLayer2() { return Layers[1]; };
	std::vector <int>& getLayer3() { return Layers[2]; };
	
	void setLayer3(std::vector <int> Layer3);
};

