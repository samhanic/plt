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
}
