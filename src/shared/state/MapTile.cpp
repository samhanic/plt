#include "MapTile.h"
#include <iostream>

using namespace state;
using namespace std;

MapTile::MapTile(TypeId id) : idStatic {id} {
    idStatic=id;
    bombDropped=false;
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

bool const MapTile::isReachable(){
    if (getTypeId()==WALL){
        return false;
    }
    return true;
}

int MapTile::isOccupied (State& state){
	// std::vector<std::unique_ptr<Robot>> & listeRobots = state.getPlayers();
	
	// /* On compare la position de la case evaluee avec celles des robots pour
    //     savoir si une unite est dessus */
	// for(size_t i=0; i < listeRobots.size(); i++){
	// 	if (position.equals(listeRobots[i]->getPosition())){
	// 		return i;
	// 	}
	// }	
	 return -1;
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
