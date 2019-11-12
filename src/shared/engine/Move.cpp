#include "Move.h"
#include "../state.h"
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Move::Move (int robotNumber, state::Action givenAction){
    robotNumber = robotNumber;
    robotAction = givenAction;
    this->directionMove = NONE;
}

bool Move::executeOrder (std::shared_ptr<state::State> theState){
    cout<<"move order executing :"<<robotAction<<endl;
    Position pos = theState->getPlayers()[0]->getPosition();
    if (directionMove==NONE){
        directionMove = theState->getPlayers()[0]->getOrientation();
    }
    
    int moveVector;
    if (robotAction == 1) {//move forward
        moveVector = 1;
    }
    else if (robotAction == 2) {//move backward
        moveVector =- 1;
    }
    if (directionMove==NONE){
        return false;
    }
    if (directionMove==NORTH) {
        pos.setY(pos.getY()-moveVector);
        if (verifyPosition(theState,pos)){
            theState->getPlayers()[0]->setPosition(pos);
        }
        else return false;
    }
    else if (directionMove==EAST){
        pos.setX(pos.getX()+moveVector);
        if (verifyPosition(theState,pos)){
            theState->getPlayers()[0]->setPosition(pos);
        }
        else return false;
    }
    else if (directionMove==SOUTH){
        pos.setY(pos.getY()+moveVector);
        if (verifyPosition(theState,pos)){
            theState->getPlayers()[0]->setPosition(pos);
        }
        else return false;
    }
    else if (directionMove==WEST){
        pos.setX(pos.getX()-moveVector);
        if (verifyPosition(theState,pos)){
            theState->getPlayers()[0]->setPosition(pos);
        }
        else return false;
    }

    MapTile *tile = theState->getMap()[pos.getY()][pos.getX()].get();
    //cout<<"X  ="<<pos.getX()<< "and Y ="<<pos.getY()<<endl;
    //If the tile is a hole, make the robot fall into.
    if (tile->getIdStatic() == BASIC){
        Basic *objective = static_cast<Basic*>(tile);
        cout<<"You arrived in a basic tile : "<<objective->getBasicTypeId()<<endl;
        if (objective->getBasicTypeId()==BASIC_HOLE){
            cout<<"You arrived in a hole!"<<endl;
        }
    } 

    //apply bonuses if there are some in the tile
    if (tile->getIdStatic() == BONUS){
        Bonus *objective = static_cast<Bonus*>(tile);
        if (objective->getRespawnTime() == 0){
            std::array<bool,5> bonusOwned = theState->getPlayers()[0]->getBonusOwned();
            if (bonusOwned[objective->getBonusTypeId()]==false){
                cout<<"Picking bonus"<<objective->getBonusTypeId()<<endl;
                bonusOwned[objective->getBonusTypeId()]=true;
                theState->getPlayers()[0]->setBonusOwned(bonusOwned);
                objective->setRespawnTime(1);
            }
            else{
                cout<<"Bonus is already owned!"<<endl;
            }
        }
        else{
            cout<<"Bonus is depleted!"<<endl;
        }
    }
    return true;
    
}


bool Move::verifyPosition(std::shared_ptr<state::State> theState, Position desiredPosition){
    //Verify that the new position robot will occupy is in the map
    if (theState->getMapWidth()==desiredPosition.getX()){
        cout<<"X is outside the map to the right"<<endl;
        return false;
    }
    if (theState->getMapHeight()==desiredPosition.getY()){
        cout<<"Y is outside the map to the bottom"<<endl;
        return false;
    }

    MapTile objective = *(theState->getMap()[desiredPosition.getX()][desiredPosition.getY()]);

    //Verify that the new position robot will occupy is not a wall
    MapTile *tile = theState->getMap()[desiredPosition.getY()][desiredPosition.getX()].get();
    if (tile->getIdStatic() == BASIC){
        Basic *objective = static_cast<Basic*>(tile);
        if (objective->getBasicTypeId()==BASIC_WALL){
            cout<<"You cannot to go over a wall!"<<endl;
            return false;
        }
    }

    //Verify that the new position robot is not occupied by a player
    for (uint i=0;i<(theState->getPlayers().size());i++){
        // cout<<"verify that"<<theState->getPlayers()[i]->getPosition().getX()<<"is ok"<<endl;
        // if (theState->getPlayers()[i]->getPosition().getX()==objective.getPosition().getX()){
        //     if(theState->getPlayers()[i]->getPosition().getY()==objective.getPosition().getY()){
        //         return false;
        //     }
        // }
    }
    //To be applied, now it crashes because of objective.getPosition()

    return true;
}

void Move::setDirectionMove(const state::DirectionStatus& directionMove){
    //Used for environment moves
    this->directionMove = directionMove;
}