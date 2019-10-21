#include <string>
#include "../../src/client/render.h"

using namespace render;

TileSet::TileSet(TileSetID newID){

	id=newID;

	if (id == MAP_TILESET){
		cellWidth=64;
		cellHeight=64;
		imageFile="res/map.png";
	}
	
	else if (id==COMMAND_TILESET){
		cellWidth=42;
		cellHeight=40;
		imageFile="res/command.png";
	}
	
	else if (id==PAWN_TILESET){
		cellWidth=64;
		cellHeight=64;
		imageFile="res/pawn.png";
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
