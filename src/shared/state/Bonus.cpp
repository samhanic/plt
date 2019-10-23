#include "../state.h"
#include <iostream>

using namespace std;
using namespace state; 

Bonus::Bonus () {
	this->bonusOrNot = true;
}

Bonus::Bonus (BonusTypeId bonusTypeId, int newX, int newY, int newTileCode) {
	/*if (bonusType == 1){
		bonusOrNor = false;
	}*/
}

BonusTypeId Bonus::getBonusTypeId() const {
	return bonusTypeId;
}

void Bonus::setBonusTypeId(BonusTypeId bonusTypeId) {
	this->bonusTypeId = bonusTypeId;
}

bool Bonus::getBonusAvailability (int respawnTime) {
	if (respawnTime == 0) {
		return this->bonusOrNot;	
	}
	else {
		cout <<  "Can't refill bonus before the end of the round";
	}
	
	return this->bonusOrNot;	
}

 void Bonus::setBonusAvailability(bool isBonus) {
	if (isBonus == false) {
		this->bonusOrNot = false;
	} else {
		this->bonusOrNot = true;
	}
}
