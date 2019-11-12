#include "../state.h"

using namespace std;
using namespace state; 

ConvBelt::ConvBelt() {

}

ConvBelt::ConvBelt(ConvBeltTypeId convBeltTypeId, int newX, int newY, int newTileCode) : MapTile(CONVBELT, newX, newY, newTileCode) {
	position.setX(newX);
	position.setY(newY);
	this->convBeltTypeId=convBeltTypeId;
	bombDropped=false;
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
