#include "Turn.h"
#include "../state.h"

using namespace engine;
using namespace state;

Turn::Turn(state::Robot& player, int actionNumberInRound) :Command (player, actionNumberInRound) {

}

void Turn::executeOrder(){
    //We gather the order to be executed and the actual rotation
    Action order = player.getRobotActions()[actionNumberInRound];
    DirectionStatus const orientation = player.getOrientation();
    //Execution
    if (order == ROTATION_CLK){
        if (orientation == NORTH){
            player.setOrientation(EAST);
        }
        else if(orientation == EAST){
            player.setOrientation(SOUTH);

        }
        else if(orientation == SOUTH){
            player.setOrientation(WEST);
        }
        else if (orientation == WEST){
            player.setOrientation(NORTH);
        }
    }
}