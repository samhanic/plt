#include "../state.h"

using namespace state; 

void Bonus::clearRefillBonus (int respawnTime, bool clearRefill) {
	/* case we want to refill bonus and counter indicates end of round */
	if (clearRefill = 1) {
		if (respawnTime == 0) {
			isEmpty =  0;
		}
	} else {
		isEmpty = 1;
	}
	
	return;	
}

void Bonus::getBonusTypeId (BonusTypeId id) {
	// to write
	return;	
}

BonusTypeId Bonus::setBonusTypeId () {
	// to write
	return 12;	
}
