#include "../state.h"

using namespace state; 

Element::Element() {
	position.setX(0);
	position.setY(0);
}

void Element::initElement() {
    this->position.setX(0);
    this->position.setY(0);
}

TypeId Element::getTypeId() const {
    return typeId;
}

void Element::setTypeId(TypeId typeId) {
   this->typeId = typeId;
}


bool Element::isReachable(){
    if (getTypeId()==WALL){
        return false;
    }
    return true;
}

state::Position Element::getPosition () {
    return position;
}

void Element::setPosition(const Position& position){
    this->position=position;
}

int Element::getTileCode (){
	return tileCode;
}

void Element::setTileCode (int newCodeTuile){
	tileCode = newCodeTuile;
}