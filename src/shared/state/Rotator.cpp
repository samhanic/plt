#include "../state.h"

using namespace state; 

RotatorTypeId Rotator::getRotatorTypeId() {
	return rotatorTypeId;
}

void Rotator::setRotatorTypeId(RotatorTypeId rotatorTypeId){
	this->rotatorTypeId = rotatorTypeId;
}
