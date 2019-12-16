#include "Move.h"
#include "../state.h"
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Move::Move (int robotNumber, state::Action givenAction){
    this->robotNumber = robotNumber;
    this->robotAction = givenAction;
    this->directionMove = NONE;
}

bool Move::executeOrder (std::shared_ptr<state::State> theState){
    //cout<<"move order executing :"<<robotAction<<endl;
    //cout<<"ROBOTNUMBER :"<<robotNumber<<endl;
    Position pos = theState->getPlayers()[robotNumber]->getPosition();
    if (directionMove==NONE){
        directionMove = theState->getPlayers()[robotNumber]->getOrientation();
    }
    
    int moveVector;
    if (robotAction == 1) {//move forward
        moveVector = 1+theState->getPlayers()[robotNumber]->getIsBoosted();
        theState->getPlayers()[robotNumber]->setIsBoosted(0);
    }
    else if (robotAction == 2) {//move backward
        moveVector = -1-theState->getPlayers()[robotNumber]->getIsBoosted();
        theState->getPlayers()[robotNumber]->setIsBoosted(0);
    }
    else if ((robotAction == 3)/*boosted move left*/ ||(robotAction == 4) /*boosted move right*/){
        /*determines position*/
        if (directionMove==NORTH) directionMove = WEST;
        else if (directionMove==WEST) directionMove = SOUTH;
        else if (directionMove==SOUTH) directionMove =EAST;
        else if (directionMove==EAST) directionMove =NORTH;
        else cout<<"Error of boosted move"<<endl;
        /*Define the move vector*/
        if (robotAction==3) moveVector = 1+theState->getPlayers()[robotNumber]->getIsBoosted(); //move right : vector is positive
        else moveVector = -1-theState->getPlayers()[robotNumber]->getIsBoosted(); //move left : vector is negative
        /*Reset the boost*/
        theState->getPlayers()[robotNumber]->setIsBoosted(0);
    }
    if (directionMove==NONE){
        return false;
    }
    if (directionMove==NORTH) {
        pos.setY(pos.getY()-moveVector);
        if (verifyPosition(theState,pos)){
            theState->getPlayers()[robotNumber]->setPosition(pos);
        }
        else return false;
    }
    else if (directionMove==EAST){
        pos.setX(pos.getX()+moveVector);
        if (verifyPosition(theState,pos)){
            theState->getPlayers()[robotNumber]->setPosition(pos);
        }
        else return false;
    }
    else if (directionMove==SOUTH){
        pos.setY(pos.getY()+moveVector);
        if (verifyPosition(theState,pos)){
            theState->getPlayers()[robotNumber]->setPosition(pos);
        }
        else return false;
    }
    else if (directionMove==WEST){
        pos.setX(pos.getX()-moveVector);
        if (verifyPosition(theState,pos)){
            theState->getPlayers()[robotNumber]->setPosition(pos);
        }
        else return false;
    }

    //If the tile is a hole, make the robot fall into.
    MapTile *tile = theState->getMap()[pos.getY()][pos.getX()].get();
    if (tile->getIdStatic() == BASIC){
        Basic *objective = static_cast<Basic*>(tile);
        //cout<<"You arrived in a basic tile : "<<objective->getBasicTypeId()<<endl;
        if (objective->getBasicTypeId()==BASIC_HOLE){
            cout<<"You arrived in a hole!"<<endl;
            theState->deathRobot(*(theState->getPlayers()[robotNumber]));
        }
    } 

    //apply bonuses if there are some in the tile
    if (tile->getIdStatic() == BONUS){
        Bonus *objective = static_cast<Bonus*>(tile);
        if (objective->getRespawnTime() == 0){
            std::array<bool,5> bonusOwned = theState->getPlayers()[robotNumber]->getBonusOwned();
            if (bonusOwned[objective->getBonusTypeId()]==false){
                cout<<"Picking bonus"<<objective->getBonusTypeId()<<endl;
                bonusOwned[objective->getBonusTypeId()]=true;
                theState->getPlayers()[robotNumber]->setBonusOwned(bonusOwned);
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
    //Validate the checkpoint if the tile is one
    if (tile->getIdStatic() == CHECKPOINT){
        CheckPoint *objective = static_cast<CheckPoint*>(tile);
        std::vector<int> newVC = theState->getPlayers()[robotNumber]->getVisitedCheckpoints();
        newVC.insert(newVC.end(),objective->getCheckPointFigure());
        theState->getPlayers()[robotNumber]->setVisitedCheckpoints(newVC);
    }
    return true;
    
}


bool Move::verifyPosition(std::shared_ptr<state::State> theState, Position desiredPosition){
    //Verify that the new position robot will occupy is in the map
    if (theState->getMapWidth()<=desiredPosition.getX()){
        cout<<"X is outside the map to the right"<<endl;
        return false;
    }
    if (theState->getMapHeight()<=desiredPosition.getY()){
        cout<<"Y is outside the map to the bottom"<<endl;
        return false;
    }

    //MapTile objective = *(theState->getMap()[desiredPosition.getX()][desiredPosition.getY()]);

    //Verify that the new position robot will occupy is not a wall
    MapTile *tile = theState->getMap()[desiredPosition.getY()][desiredPosition.getX()].get();
    if (tile->getIdStatic() == BASIC){
        Basic *objective = static_cast<Basic*>(tile);
        if (objective->getBasicTypeId()==BASIC_WALL){
            cout<<"You cannot go over a wall!"<<endl;
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