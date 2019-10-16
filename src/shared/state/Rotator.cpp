#include "../state.h"

using namespace state; 

RotatorTypeId Rotator::getRotatorTypeId() const {
	return rotatorTypeId;
}

void Rotator::setRotatorTypeId(RotatorTypeId rotatorTypeId){
	this->rotatorTypeId = rotatorTypeId;
}
