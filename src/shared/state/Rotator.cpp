#include "../state.h"

using namespace state; 

Rotator::Rotator() {
}

Rotator::Rotator (RotatorTypeId rotatorTypeId, int newX, int newY, int newTileCode) {
}

RotatorTypeId Rotator::getRotatorTypeId() {
	return rotatorTypeId;
}

void Rotator::setRotatorTypeId(RotatorTypeId rotatorTypeId){
	this->rotatorTypeId = rotatorTypeId;
}
