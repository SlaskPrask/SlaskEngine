#include <rapidxml/rapidxml.hpp>
#include <iostream>
#include <vector>

#pragma once

//MOST OF THIS CODE IS COPIED, DON'T JUDGE,
//Zas read through this shit, i did some changes and comented a bunch of stuff, it should work but I don't know.


class TMXMapTileSet 
{
public:
	int firstGid; //first global tile id
	std::string name; //name of tileset
	int tileWidth; //the maximum width of tiles in this tileset
	int tileHeight; //the maximum height of tiles in this tileset
	std::string filename; //NAME OF FILE CONTAINING THE TILESET????????

};

class TMXMapLayer 
{
public:
	std::string name; //name of the layer
	int width;  //not needed as of QT
	int height; //not needed as of QT
	int* data; //important maybe: http://doc.mapeditor.org/reference/tmx-map-format/#data

	~TMXMapLayer();
};

class TMXMapObjectProperty 
{
public:
	std::string name; //name of the property
	std::string value; //the value of the property 
	//type can be different as of 0.16 http://doc.mapeditor.org/reference/tmx-map-format/#property
};

class TMXMapObject 
{
public:
	std::string name; //name of the object, arbitrary string?
	int gid; //A reference to a tile
	int x; //the x coordinate of the object in pixels
	int y; // as above but y
	int width; //the widht of the object in pixels, defaults to 0
	int height; //same as above dumbass
	std::vector<TMXMapObjectProperty*> properties; //lists of properties

	~TMXMapObject();
};

class TMXMapObjectGroup
{
public:
	std::string name; //name of the object group
	bool visible; //if the layer is shown

	std::vector<TMXMapObject*> objects; 

	~TMXMapObjectGroup();
};

class TMXMap 
{
public:
	int width; //map width in tiles
	int height; //map height in tiles
	int tileWidth; //the width of a tile in pixels?
	int tileHeight; //the height of a tile in pixels?

	std::vector<TMXMapTileSet*> tilesets;
	std::vector<TMXMapLayer* > layers;
	std::vector<TMXMapObjectGroup* > groups;

	~TMXMap();

};


TMXMap* LoadTMXMap(char *xml);


class TMXparser
{
public:
	TMXparser();
	~TMXparser();
};

