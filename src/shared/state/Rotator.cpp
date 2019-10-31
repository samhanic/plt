#include "../state.h"

using namespace state; 

Rotator::Rotator() {
}

Rotator::Rotator (RotatorTypeId rotatorTypeId, int newX, int newY, int newTileCode):MapTile(ROTATOR, newX, newY, newTileCode) {
	position.setX(newX);
	position.setY(newY);
	rotatorTypeId=rotatorTypeId;
	idStatic=ROTATOR;
	bombDropped=false;
}

RotatorTypeId Rotator::getRotatorTypeId() const {
	return rotatorTypeId;
}

void Rotator::setRotatorTypeId(RotatorTypeId rotatorTypeId){
	this->rotatorTypeId = rotatorTypeId;
}
