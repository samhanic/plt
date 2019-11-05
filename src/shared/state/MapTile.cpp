#include "MapTile.h"
#include <iostream>

using namespace state;
using namespace std;

MapTile::MapTile(){
    idStatic=NO_ID;
    bombDropped=false;
}

MapTile::MapTile(TypeId id) : idStatic {id} {
    idStatic=id;
    bombDropped=false;
}

MapTile::MapTile (TypeId id, int newX, int newY, int newCodeTuile) : idStatic {id}{
    idStatic=id;
    bombDropped=false;
    position.setX(newX);
    position.setY(newY);
    tileCode=newCodeTuile;
}

bool MapTile::isStatic(){
	return true;
}

void MapTile::dropBomb(void){
    bombDropped=true;
}
void MapTile::removeBomb(void){
    bombDropped=false;
}

TypeId MapTile::getIdStatic() const{
    return idStatic;
}

void MapTile::setIdStatic(TypeId idStatic){
    this->idStatic = idStatic;
}

bool MapTile::getBombDropped() const{
    return bombDropped;
}

void MapTile::setBombDropped(bool bombDropped){
    this->bombDropped = bombDropped;
}
