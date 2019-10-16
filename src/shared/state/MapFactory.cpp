#include "../state.h"
#include <iostream>

using namespace std;
using namespace state;

MapFactory::MapFactory() {
	convertMapBonus[0] = BONUS_HEAL;
	convertMapBonus[1] = BONUS_AUTO_ATTACK;
	convertMapBonus[2] = BONUS_SHIELD;
	convertMapBonus[3] = BONUS_CROSS_ATTACK;
	convertMapBonus[4] = BONUS_BOMB;
	
	convertMapConvBelt[0] = CB_N_S;
    convertMapConvBelt[1] = CB_E_W;
    convertMapConvBelt[2] = CB_S_N;
    convertMapConvBelt[3] = CB_W_E;
    convertMapConvBelt[4] = CB_N_E;
    convertMapConvBelt[5] = CB_N_W;
    convertMapConvBelt[6] = CB_E_N;
    convertMapConvBelt[7] = CB_E_S;
    convertMapConvBelt[8] = CB_S_E;
    convertMapConvBelt[9] = CB_S_W;
    convertMapConvBelt[10] = CB_W_N;
    convertMapConvBelt[11] = CB_W_S;
    convertMapConvBelt[11] = CB_NW_E;
    
    convertMapRotator[0] = ROT_CLK;
    convertMapRotator[1] = ROT_CCLK;
    
    convertMapOthers[0] = ROBOT;
    convertMapOthers[1] = NORMAL_TILE;
    convertMapOthers[2] = CHECKPOINT;
    convertMapOthers[3] = HOLE;
    convertMapOthers[4] = WALL;
    convertMapOthers[5] = BONUS;
    convertMapOthers[6] = ROTATOR;
    convertMapOthers[7] = CONVBELT;    
}

std::map<int, BonusTypeId>& MapFactory::doConvertMapBonus () {
	std::map<int, BonusTypeId>& bonusFactory = convertMapBonus;
	return bonusFactory;
}

std::map<int, ConvBeltTypeId>& MapFactory::doConvertMapConvBelt () {
	std::map<int, ConvBeltTypeId>& convBeltFactory = convertMapConvBelt;
	return convBeltFactory;
}

std::map<int, RotatorTypeId>& MapFactory::doConvertMapRotator () {
	std::map<int, RotatorTypeId>& rotatorFactory = convertMapRotator;
	return rotatorFactory;
}

std::map<int, TypeId>& MapFactory::doConvertMapOthers () {
	std::map<int, TypeId>& othersFactory = convertMapOthers;
	return othersFactory;
}
