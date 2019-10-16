#include "MapTile.h"

using namespace state;

MapTile::MapTile(TypeId id) : idStatic {id} {
    idStatic=id;
    bombDropped=false;
}

void MapTile::dropBomb(void){
    bombDropped=true;
}

void MapTile::removeBomb(void){
    bombDropped=false;
}

<<<<<<< HEAD
bool MapTile::isStatic(){
	return true;
}

bool const MapTile::isReachable(){
    return 1;
=======
bool const MapTile::isStatic(){
    return true;
}

bool const MapTile::isReachable(){
    return true;
>>>>>>> master
}
