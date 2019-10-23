#include "../state.h"

using namespace state; 

Rotator::Rotator() {
}

RotatorTypeId Rotator::getRotatorTypeId() {
	return rotatorTypeId;
}

void Rotator::setRotatorTypeId(RotatorTypeId rotatorTypeId){
	this->rotatorTypeId = rotatorTypeId;
}
