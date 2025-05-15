#include "mapa.h"
#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <fstream>

Mapa::Mapa()
{
	_width = 0;
	_height = 0;
	_tileWidth = 0;
	_tileHeight = 0;
	tilemap = 0;

	for (size_t i = 0; i < 1; i++)
	{
		Layers[i].resize(0);
	}

	_CameraX = 0;
}

Mapa::~Mapa()
{
}

int Mapa::loadMap(const char * filename, const char * imagename)
{
	using namespace tinyxml2;

	XMLDocument doc;
	if (doc.LoadFile(filename) != XML_SUCCESS)
	{
		std::cout << "ERROR: " << doc.ErrorStr();
		return 1;
	}
	XMLElement* map = doc.FirstChildElement();
	_width = std::stoi(map->Attribute("width"));
	_height = std::stoi(map->Attribute("height"));
	_tileWidth = std::stoi(map->Attribute("tilewidth"));
	_tileHeight = std::stoi(map->Attribute("tileheight"));

	XMLElement* tileset = map->FirstChildElement("tileset");

	//id = rm->loadAndGetGraphicID("tileset.png");
	//_tiles.setFirstID(std::stoi(tileset->Attribute("firstgid")));
	_tiles.setTileWidth(getTileWidth());
	_tiles.setTilesHeight(getTileHeight());

	XMLElement* layer = map->FirstChildElement("layer");
	for (size_t i = 0; i < NUM_CAPAS; i++)
	{
		std::string layerTXT;
		layerTXT = layer->FirstChildElement("data")->GetText();

		tilemap = rm->loadAndGetGraphicID(imagename);

		size_t pos = 0;
		size_t nextPos = 0;
		while (nextPos != std::string::npos)
		{
			nextPos = layerTXT.find(',', pos);
			if (nextPos != std::string::npos)
			{
				int value = std::stoi(layerTXT.substr(pos, nextPos - pos));
				Layers[i].push_back(value);
				//std::cout << value << "\n";
				pos = nextPos + 1;
			}
			else
			{
				int value = std::stoi(layerTXT.substr(pos, layerTXT.size() - pos));
				Layers[i].push_back(value);
				//std::cout << value << "\n";
			}
		}
		layer = layer->NextSiblingElement("layer");
	}

	/*int j = 0;
	for (size_t i = 0; i < Layers->size(); i++)
	{
		std::cout << Layers->at(i) << ",";
		j++;
		if (j == _width)
		{
			std::cout << std::endl;
			j = 0;
		}
	}*/

	/*saveBinary();
	readBinary("example.bin");*/

	return 0;
}

void Mapa::render()
{
	int count = 0;
	int _spriteX = 0;
	int _spriteY = 0;
	int _id = 0;

	for (size_t y = 0; y < NUM_CAPAS; y++)
	{
		count = 0;
		for (size_t i = 0; i < _height; i++)
		{
			for (size_t j = 0; j < _width; j++)
			{
				_id = Layers[y].at(count) - 1;
				//std::cout << _id << std::endl;

				if (_id >= 0)
				{
					int CellX = _id % 15;
					int CellY = _id / 15;

					_spriteX = CellX * (getTileWidth() + 1);
					_spriteY = CellY * (getTileHeight() + 1);

					vid->renderGraphic(tilemap, _tileWidth * j, _tileHeight * i, _tileWidth, _tileHeight, _spriteX, _spriteY);
				}
				count++;
			}
		}
	}
}

int Mapa::getIDfromLayer(int layer, int PosX, int PosY)
{
	int TileX = PosX / _tileWidth;
	int TileY = PosY / _tileHeight;
	return Layers[layer][TileY * _width + TileX];
}

void Mapa::saveBinary()
{
	std::fstream file("example.bin", std::ios::out | std::ios::binary);
	file.write(reinterpret_cast<const char*>(&_width), sizeof(unsigned short int));
	file.write(reinterpret_cast<const char*>(&_height), sizeof(unsigned short int));

	for (size_t j = 0; j < NUM_CAPAS; j++)
	{
		for (size_t i = 0; i < Layers[j].size(); i++)
		{
			file.write(reinterpret_cast<const char*>(&Layers[j][i]), sizeof(unsigned short int));
		}
	}
		
	file.close();
}

void Mapa::readBinary(const char* filename)
{
	std::fstream file(filename, std::ios::in | std::ios::binary);
	file.read(reinterpret_cast<char*>(&_width), sizeof(unsigned short int));
	file.read(reinterpret_cast<char*>(&_height), sizeof(unsigned short int));

	for (size_t j = 0; j < NUM_CAPAS; j++)
	{
		for (size_t i = 0; i < Layers[j].size(); i++)
		{
			int layerValue;
			file.read(reinterpret_cast<char*>(&layerValue), sizeof(unsigned short int));
			Layers1[j].push_back(layerValue);
		}
	}

	if (Layers[0] == Layers1[0])
	{
		std::cout << "Si" << std::endl;
	}
	else
	{
		std::cout << "No" << std::endl;
	}

	file.close();
}

