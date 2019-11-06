#include "Rotation.h"
#include "../state.h"

using namespace engine;
using namespace state;
using namespace std;

Rotation::Rotation (int robotNumber, int givenAction) {
    robotNumber = robotNumber;
    robotAction = givenAction;
}


bool Rotation::executeOrder(std::shared_ptr<state::State> theState){
    /*We gather the order to be executed and the actual rotation*/
    
    if (robotAction == 6){ // rotation clk
        if (orientation == NORTH){
            theState->getPlayers()[0]->setOrientation(EAST);
        }
        else if(orientation == EAST){
            player->setOrientation(SOUTH);

        }
        else if(orientation == SOUTH){
            player->setOrientation(WEST);
        }
        else if (orientation == WEST){
            player->setOrientation(NORTH);
        }
    }
    else if (robotAction == 7){
        if (orientation == NORTH){
            player->setOrientation(WEST);
        }
        else if(orientation == EAST){
            player->setOrientation(NORTH);

        }
        else if(orientation == SOUTH){
            player->setOrientation(EAST);
        }
        else if (orientation == WEST){
            player->setOrientation(SOUTH);
        }
    }
}