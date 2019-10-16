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

bool const MapTile::isStatic(){
    return true;
}

bool const MapTile::isReachable(){
    return true;
}
