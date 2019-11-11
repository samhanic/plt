#include "../state.h"

using namespace state;

Basic::Basic() {
}

Basic::Basic (BasicTypeId basicTypeId, int newX, int newY, int newTileCode):MapTile(BASIC, newX, newY, newTileCode) {
	position.setX(newX);
	position.setY(newY);
	this->basicTypeId = basicTypeId;
}

BasicTypeId Basic::getBasicTypeId() const {
	return basicTypeId;
}

void Basic::setBasicTypeId(BasicTypeId basicTypeId){
	this->basicTypeId = basicTypeId;
}
