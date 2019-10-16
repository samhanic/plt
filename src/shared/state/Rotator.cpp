<<<<<<< HEAD
#include "../state.h"

using namespace state; 

void Rotator::moveRobotOnRotator (Action action) {
	// to write
	return;	
}
=======
#include "Rotator.h"

using namespace state;

Rotator::Rotator(bool isClk){
    if (isClk){
        rotatorTypeId=ROT_CLK;
    }
    else{
        rotatorTypeId=ROT_CCLK;
    }
    isEmpty=true;
}

bool const Rotator::isReachable(){
    return not(isEmpty);
}

bool Rotator::equals(){
    return true;
}
>>>>>>> master
