#include "../state.h"
#include <iostream>

using namespace std;
using namespace state; 

ConvBelt::ConvBelt() {

}

ConvBelt::ConvBelt(ConvBeltTypeId convBeltTypeId, int newX, int newY, int newTileCode) : MapTile(CONVBELT, newX, newY, newTileCode) {
}

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
