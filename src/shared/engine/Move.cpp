#include "Move.h"
#include "../state.h"
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

 Move::Move (int robotNumber, state::Action givenAction){
    robotNumber = robotNumber;
    robotAction = givenAction;
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

    //apply bonuses if there are some in the tile
    //MapTile objective = *(theState->getMap()[pos.getX()][pos.getY()]);
    MapTile *tile = theState->getMap()[pos.getY()][pos.getX()].get();
    cout<<"X  ="<<pos.getX()<< "and Y ="<<pos.getY()<<endl;
    //cout<< "You arrived in a "<< tile->getIdStatic()<< " tile."<<endl;
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
    
}


bool Move::verifyPosition(std::shared_ptr<state::State> theState, Position desiredPosition){
    //Verify that the new position robot will occupy is not a wall and not occupied by a player
    //Position oldPos = theState->getPlayers()[0]->getPosition();
    MapTile objective = *(theState->getMap()[desiredPosition.getX()][desiredPosition.getY()]);

    //checks if this is not a wall
    if (objective.isWall){
        return false;
    }

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