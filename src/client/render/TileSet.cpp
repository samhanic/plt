#include <string>
#include "../../src/client/render.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <map>
#include <memory>
#include <unistd.h>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>	

using namespace render;

TileSet::TileSet(TileSetID newID){

	id=newID;

	if (id == MAP_TILESET){
		cellWidth=64;
		cellHeight=64;
		imageFile="../res/map.png";
	} else if (id==PAWN_TILESET){
		cellWidth=64;
		cellHeight=64;
		imageFile="../res/pawn.png";
	} else if (id==COMMAND_TILESET){
		cellWidth=40;
		cellHeight=40;
		imageFile="../res/command.png";
	}
	
	textureTileset.loadFromFile(imageFile);
}

const int TileSet::getTileSetID(){
	return id;
}

const int TileSet::getCellWidth(){
	return cellWidth;
}

const int TileSet::getCellHeight(){
	return cellHeight;
}

const std::string  TileSet::getImageFile (){
	return imageFile;
}

sf::Texture& TileSet::getTexture(){
	sf::Texture & refTexture = textureTileset;
	return refTexture;
}
