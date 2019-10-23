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
	
	convertMapConvBelt[5] = CB_N_S;
    convertMapConvBelt[6] = CB_E_W;
    convertMapConvBelt[7] = CB_S_N;
    convertMapConvBelt[8] = CB_W_E;
    convertMapConvBelt[9] = CB_N_E;
    convertMapConvBelt[10] = CB_N_W;
    convertMapConvBelt[11] = CB_E_N;
    convertMapConvBelt[12] = CB_E_S;
    convertMapConvBelt[13] = CB_S_E;
    convertMapConvBelt[14] = CB_S_W;
    convertMapConvBelt[15] = CB_W_N;
    convertMapConvBelt[16] = CB_W_S;
    convertMapConvBelt[17] = CB_NW_E;
    
    convertMapRotator[18] = ROT_CLK;
    convertMapRotator[19] = ROT_CCLK;
    
    convertMapOthers[20] = ROBOT;
    convertMapOthers[21] = NORMAL_TILE;
    convertMapOthers[22] = CHECKPOINT;
    convertMapOthers[23] = HOLE;
    convertMapOthers[24] = WALL;
    convertMapOthers[25] = BONUS;
    convertMapOthers[26] = ROTATOR;
    convertMapOthers[27] = CONVBELT;    
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
