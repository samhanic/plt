#include "Rotation.h"
#include "../state.h"

using namespace engine;
using namespace state;
using namespace std;

Rotation::Rotation(state::Robot& player, int actionNumberInRound) :Command (player, actionNumberInRound) {

}

bool Rotation::executeOrder(state::State& myState){
    /*We gather the order to be executed and the actual rotation*/
    Action order = player->getRobotActions()[actionNumberInRound];
    DirectionStatus const orientation = player->getOrientation();
    /*Execution*/
    if (order == ROTATION_CLK){
        if (orientation == NORTH){
            player->setOrientation(EAST);
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
    else if (order == ROTATION_CCLK){
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