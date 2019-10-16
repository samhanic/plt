#include "../state.h"
#include <iostream>

using namespace std;
using namespace state; 

ConvBeltTypeId ConvBelt::getConvBeltTypeId() const {
	return convBeltTypeId;
}

void ConvBelt::setConvBeltTypeId(ConvBeltTypeId convBeltTypeId) {
	this->convBeltTypeId = convBeltTypeId;
}

bool ConvBelt::getConvBeltSpeed(){
	return fastOrNot;
}
/*
void ConvBelt::getConvBeltSpeed (ConvBeltTypeId id) {
	// to write
	return;	
}

ConvBeltTypeId ConvBelt::setConvBeltSpeed () {
	// to write
	return 12;	
}
*/