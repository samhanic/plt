#include "Rotation.h"
#include "../state.h"
#include "../engine.h"
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Rotation::Rotation (int robotNumber, state::Action givenAction) {
    this->robotNumber = robotNumber;
    this->robotAction = givenAction;
}


bool Rotation::executeOrder(std::shared_ptr<state::State> theState){
    /*We gather the order to be executed and the actual rotation*/

    orientation = theState->getPlayers()[robotNumber]->getOrientation();
    /* Case of a clockwise rotation */
    if (robotAction == 6){
        if (orientation == NORTH){
            theState->getPlayers()[robotNumber]->setOrientation(EAST);
        }
        else if(orientation == EAST){
            theState->getPlayers()[robotNumber]->setOrientation(SOUTH);
        }
        else if(orientation == SOUTH){
            theState->getPlayers()[robotNumber]->setOrientation(WEST);
        }
        else if (orientation == WEST){
            theState->getPlayers()[robotNumber]->setOrientation(NORTH);
        }
    }
    /* Case of a counter clockwise rotation */
    else if (robotAction == 5){
        if (orientation == NORTH){
            theState->getPlayers()[robotNumber]->setOrientation(WEST);
        }
        else if(orientation == EAST){
            theState->getPlayers()[robotNumber]->setOrientation(NORTH);
        }
        else if(orientation == SOUTH){
            theState->getPlayers()[robotNumber]->setOrientation(EAST);
        }
        else if (orientation == WEST){
            theState->getPlayers()[robotNumber]->setOrientation(SOUTH);
        }
    }
    return 0;
}