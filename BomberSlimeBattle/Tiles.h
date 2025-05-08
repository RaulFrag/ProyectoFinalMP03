#pragma once
class Tiles
{
	int _firstID;
	int _tileWidth;
	int _tileHeight;

	const char* _filename;

	
public:
	Tiles();
	~Tiles();

	void setFirstID(int id) { _firstID = id; };
	void setTileWidth(int width) { _tileWidth = width; };
	void setTilesHeight(int height) { _tileHeight = height; };
};