#include "Attack.h"
#include "../state.h"
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Attack::Attack(int robotNumber){
    this->robotNumber=robotNumber;
}

bool Attack::executeOrder(std::shared_ptr<state::State> theState) {
    //int distance =0;
    bool ableAttack=true;
    int x = theState->getPlayers()[robotNumber]->getPosition().getX();
    int y = theState->getPlayers()[robotNumber]->getPosition().getY();
    state::DirectionStatus orientation = theState->getPlayers()[robotNumber]->getOrientation();
    while (ableAttack){
        //Update position where attack is done
        if (orientation==NORTH) --y;
        else if (orientation==EAST) ++x;
        else if (orientation==SOUTH)++y;
        else if (orientation==WEST) --x;
        else cout<<"Problem of orientation"<<endl;

        //Verify that the position is in the range of the map
        if (x<0 || x> theState->getMapWidth() || y<0 || y>theState->getMapHeight()){
            cout << "You attacked but nobody was in this direction !"<<endl;
            ableAttack=false;
            return false;
        }
        //search for robot in this position
        for (size_t i=0; i<theState->getPlayers().size(); ++i){
            if (theState->getPlayers()[i]->getPosition().getX()==x && theState->getPlayers()[i]->getPosition().getY()==y){
                ableAttack=false;
                theState->getPlayers()[i]->setLifePoints(theState->getPlayers()[i]->getLifePoints()-1);
                cout<<"You correctly attacked the robot no "<<i<<". Congrats !"<<endl;
                return true;
            }
        }
    }
    return false;
}
