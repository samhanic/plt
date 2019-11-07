#include "Rotation.h"
#include "../state.h"
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Rotation::Rotation (int robotNumber, int givenAction) {
    robotNumber = robotNumber;
    robotAction = givenAction;
}


bool Rotation::executeOrder(std::shared_ptr<state::State> theState){
    /*We gather the order to be executed and the actual rotation*/
    orientation = theState->getPlayers()[0]->getOrientation();
    cout<<"rotation detected : "<<robotAction<<". orientation avant :"<<theState->getPlayers()[0]->getOrientation()<<endl;
    
    if (robotAction == 5){ // rotation clk
        
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
    else if (robotAction == 6){ // rotation cclk
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
    cout<<"orientaytion apres fonction"<<theState->getPlayers()[0]->getOrientation()<<endl;
    return 0;
}