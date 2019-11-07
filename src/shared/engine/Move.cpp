#include "Move.h"
#include "../state.h"
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;


Move::Move (int robotNumber, int givenAction){
    robotNumber = robotNumber;
    robotAction =givenAction;
}

void Move::executeOrder (std::shared_ptr<state::State> theState){
    cout<<"move order executing :"<<robotAction<<endl;
    Position pos = theState->getPlayers()[0]->getPosition();
    DirectionStatus direction = theState->getPlayers()[0]->getOrientation();

    int moveVector;
    if (robotAction==1){//move forward
        moveVector=1;
    }
    else if(robotAction==2){//move backward
        moveVector =-1;
    }

    if (direction==NORTH){
        pos.setY(pos.getY()-moveVector);
        if (verifyPosition(theState,pos)){
            theState->getPlayers()[0]->setPosition(pos);
        }
    }
    else if (direction==EAST){
        pos.setX(pos.getX()+moveVector);
        if (verifyPosition(theState,pos)){
            theState->getPlayers()[0]->setPosition(pos);
        }
    }
    else if (direction==SOUTH){
        pos.setY(pos.getY()+moveVector);
        if (verifyPosition(theState,pos)){
            theState->getPlayers()[0]->setPosition(pos);
        }
    }
    else if (direction==WEST){
        pos.setX(pos.getX()-moveVector);
        if (verifyPosition(theState,pos)){
            theState->getPlayers()[0]->setPosition(pos);
        }
    }
    
}


bool Move::verifyPosition(std::shared_ptr<state::State> theState, Position desiredPosition){
    //Verify that the new position robot will occupy is not a wall and not occupied by a player
    Position oldPos = theState->getPlayers()[0]->getPosition();
    MapTile objective = *(theState->getMap()[desiredPosition.getX()][desiredPosition.getY()]);

    //checks if this is not a wall
    if (objective.isWall){
        return false;
    }

    // for (int i=0;i=(theState->getPlayers().size());i++){
    //     if (theState->getPlayers()[i]->getPosition().getX()==objective.getPosition().getX()){
    //         if(theState->getPlayers()[i]->getPosition().getY()==objective.getPosition().getY()){
    //             return false;
    //         }
    //     }
    // }
    //To be applied, now it crashes because of objective.getPosition()

    return true;
}