<<<<<<< HEAD
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
=======
#include "Bonus.h"

using namespace state;

Bonus::Bonus(BonusTypeId BonusType){
    isEmpty=false;
    respawnTime=0;
    type=BonusType;
}

bool Bonus::clearBonus (){
    isEmpty=true;
    respawnTime=3;
}

void Bonus::replenishBonus(int respawnTime){
    respawnTime--;
    if (respawnTime==0){
        isEmpty=false;
    }
}

bool const Bonus::isReachable(){
    return not(isEmpty);
>>>>>>> master
}
