#include "../state.h"
#include <iostream>

using namespace std;
using namespace state;

MapFactory::MapFactory() {
	convertMapBonus[27] = BONUS_HEAL;
	convertMapBonus[28] = BONUS_AUTO_ATTACK;
	convertMapBonus[29] = BONUS_SHIELD;
	convertMapBonus[30] = BONUS_CROSS_ATTACK;
	convertMapBonus[31] = BONUS_BOMB;
	
	convertMapConvBelt[13] = CB_E_S;
    convertMapConvBelt[14] = CB_W_S;
    convertMapConvBelt[15] = CB_S_E;
    convertMapConvBelt[16] = CB_S_W;
    convertMapConvBelt[17] = CB_N_E;
    convertMapConvBelt[18] = CB_W_N;
    convertMapConvBelt[19] = CB_E_N;
    convertMapConvBelt[20] = CB_N_W;
    convertMapConvBelt[21] = CB_N_S;
    convertMapConvBelt[22] = CB_S_N;
    convertMapConvBelt[23] = CB_E_W;
    convertMapConvBelt[24] = CB_W_E;
    convertMapConvBelt[25] = CB_NW_E;
    
    convertMapRotator[32] = ROT_CLK;
    convertMapRotator[33] = ROT_CCLK;
    
    convertMapBasic[0] = BASIC_NORMAL_TILE;
    convertMapBasic[1] = BASIC_HOLE;
    convertMapBasic[2] = BASIC_WALL;

    convertMapCheckPoint[3]= CP_ONE;
    convertMapCheckPoint[4]= CP_TWO;
    convertMapCheckPoint[5]= CP_THREE;
    convertMapCheckPoint[6]= CP_FOUR;
    convertMapCheckPoint[7]= CP_FIVE;
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

std::map<int, BasicTypeId>& MapFactory::doConvertMapBasic () {
	std::map<int, BasicTypeId>& basicFactory = convertMapBasic;
	return basicFactory;
}

std::map<int, CheckPointTypeId>& MapFactory::doConvertMapCheckPoint () {
	std::map<int, CheckPointTypeId>& checkPointFactory = convertMapCheckPoint;
	return checkPointFactory;
}
