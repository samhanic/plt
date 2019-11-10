#include "Rotation.h"
#include "../state.h"
#include "../engine.h"
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Rotation::Rotation (int robotNumber, state::Action givenAction) {
    robotNumber = robotNumber;
    robotAction = givenAction;
}


bool Rotation::executeOrder(std::shared_ptr<state::State> theState){
    /*We gather the order to be executed and the actual rotation*/

    orientation = theState->getPlayers()[0]->getOrientation();
    /* Case of a clockwise rotation */
    if (robotAction == 6){
        if (orientation == NORTH){
            theState->getPlayers()[0]->setOrientation(EAST);
        }
        else if(orientation == EAST){
            theState->getPlayers()[0]->setOrientation(SOUTH);
        }
        else if(orientation == SOUTH){
            theState->getPlayers()[0]->setOrientation(WEST);
        }
        else if (orientation == WEST){
            theState->getPlayers()[0]->setOrientation(NORTH);
        }
    }
    /* Case of a counter clockwise rotation */
    else if (robotAction == 5){
        if (orientation == NORTH){
            theState->getPlayers()[0]->setOrientation(WEST);
        }
        else if(orientation == EAST){
            theState->getPlayers()[0]->setOrientation(NORTH);
        }
        else if(orientation == SOUTH){
            theState->getPlayers()[0]->setOrientation(EAST);
        }
        else if (orientation == WEST){
            theState->getPlayers()[0]->setOrientation(SOUTH);
        }
    }
    return 0;
}