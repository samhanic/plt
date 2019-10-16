#include "../state.h"
#include <iostream>

using namespace std;
using namespace state; 


bool ConvBelt::getConvBeltSpeed(){
	return fastOrNot;
}

void ConvBelt::setConvBeltSpeed (bool setSpeed){
	fastOrNot=setSpeed;
}

ConvBeltTypeId ConvBelt::getConvBeltTypeId() const {
	return convBeltTypeId;
}

void ConvBelt::setConvBeltTypeId(ConvBeltTypeId convBeltTypeId){
	this->convBeltTypeId = convBeltTypeId;
}
