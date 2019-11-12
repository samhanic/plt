#include "EnvironmentMove.h"
#include "../state.h"
#include "../engine.h"
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

EnvironmentMove::EnvironmentMove(){
    this->robotNumber = 0;
}

EnvironmentMove::EnvironmentMove (int robotNumber){
    this->robotNumber = robotNumber;
}

EnvironmentMove::EnvironmentMove (int robotNumber, EMType type){
    this->robotNumber = robotNumber;
    this->type=type;
}

void EnvironmentMove::setType(EMType type){
    this->type = type;
}

bool EnvironmentMove::execute (std::shared_ptr<state::State> theState){
    Robot *robot = theState->getPlayers()[robotNumber].get();
    MapTile *tileRobot = theState->getMap()[robot->getPosition().getY()][robot->getPosition().getX()].get();
    cout<<"Executing environments actions for tile"<<tileRobot->getIdStatic()<<"located in X="<<robot->getPosition().getX()<<"and Y="<<robot->getPosition().getY()<<endl;
    if (tileRobot->getIdStatic()==ROTATOR){
        cout<<"A rotator will move you"<<endl;
        Rotator *tileRobotRotator = static_cast<Rotator*>(tileRobot);
        if (tileRobotRotator->getRotatorTypeId()==ROT_CLK){
            Rotation *environmentRotation = new Rotation(robotNumber,ROTATION_CLK);
            environmentRotation->executeOrder(theState);
        }
        if (tileRobotRotator->getRotatorTypeId()==ROT_CCLK){
            Rotation *environmentRotation = new Rotation(robotNumber,ROTATION_CCLK);
            environmentRotation->executeOrder(theState);
        }
    }

    if (tileRobot->getIdStatic()==CONVBELT){
        cout<<"A convbelt will move you"<<endl;
        //Move the robot
        ConvBelt *tileRobotCB = static_cast<ConvBelt*>(tileRobot);
        Move *environmentMove = new Move (robotNumber,FORWARD);
        if ((tileRobotCB->getConvBeltTypeId()==CB_S_N) || (tileRobotCB->getConvBeltTypeId()==CB_E_N) || (tileRobotCB->getConvBeltTypeId()==CB_W_N)){
            environmentMove->setDirectionMove(NORTH);
            cout<<"This convbelt is of type :"<<tileRobotCB->getConvBeltTypeId()<<" and will go to north"<<endl;
        }
        else if((tileRobotCB ->getConvBeltTypeId()==CB_W_E) || (tileRobotCB->getConvBeltTypeId()==CB_N_E) || (tileRobotCB->getConvBeltTypeId()==CB_S_E)){
            environmentMove->setDirectionMove(EAST);
            cout<<"This convbelt is of type :"<<tileRobotCB->getConvBeltTypeId()<<" and will go to east"<<endl;
        }
        else if ((tileRobotCB->getConvBeltTypeId()==CB_N_S) || (tileRobotCB->getConvBeltTypeId()==CB_E_S) || (tileRobotCB->getConvBeltTypeId()==CB_W_S)){
            environmentMove->setDirectionMove(SOUTH);
            cout<<"This convbelt is of type :"<<tileRobotCB->getConvBeltTypeId()<<" and will go to south"<<endl;
        }
        else if ((tileRobotCB->getConvBeltTypeId()==CB_E_W) || (tileRobotCB->getConvBeltTypeId()==CB_S_W) || (tileRobotCB->getConvBeltTypeId()==CB_N_W)){
            environmentMove->setDirectionMove(WEST);
            cout<<"This convbelt is of type :"<<tileRobotCB->getConvBeltTypeId()<<" and will go to west"<<endl;
        }
        else{
            cout<<"This type of cb has not been yet implemented : "<<tileRobotCB->getConvBeltTypeId()<<endl;
            environmentMove->setDirectionMove(NONE);
        }
        environmentMove->executeOrder(theState);
        //Then rotate it
        if ((tileRobotCB->getConvBeltTypeId()==CB_S_E) || (tileRobotCB->getConvBeltTypeId()==CB_W_S) || (tileRobotCB->getConvBeltTypeId()==CB_N_W) || (tileRobotCB->getConvBeltTypeId()==CB_E_N)){
            Rotation *environmentalRotation = new Rotation(0,ROTATION_CLK);
            environmentalRotation->executeOrder(theState);
        }
        else if((tileRobotCB->getConvBeltTypeId()==CB_S_W) || (tileRobotCB->getConvBeltTypeId()==CB_W_N) || (tileRobotCB->getConvBeltTypeId()==CB_N_E) || (tileRobotCB->getConvBeltTypeId()==CB_E_S)){
            Rotation *environmentalRotation = new Rotation(0,ROTATION_CCLK);
            environmentalRotation->executeOrder(theState);
        }
    }
    return true;
}

bool EnvironmentMove::grabEMType(std::shared_ptr<state::State> theState){
    Robot *robot = theState->getPlayers()[robotNumber].get();
    MapTile *tileRobot = theState->getMap()[robot->getPosition().getY()][robot->getPosition().getX()].get();
    if (tileRobot->getTypeId()==ROTATOR){
        Rotator *tileRobotRotator = static_cast<Rotator*>(tileRobot);
        if(tileRobotRotator->getRotatorTypeId()==ROT_CLK){
            this->type=EM_ROTATION_CLK;
            return true;
        }
        else if (tileRobotRotator->getRotatorTypeId()==ROT_CCLK){
            this->type=EM_ROTATION_CCLK;
            return true;
        }
    }
    if (tileRobot->getTypeId()==CONVBELT){
        ConvBelt *tileRobotCB = static_cast<ConvBelt*>(tileRobot);
        if((tileRobotCB->getConvBeltTypeId()==CB_N_S) || (tileRobotCB->getConvBeltTypeId()==CB_E_S) || (tileRobotCB->getConvBeltTypeId()==CB_W_S)){
            this->type=EM_CB_SOUTH;
        }
        if((tileRobotCB->getConvBeltTypeId()==CB_N_E) || (tileRobotCB->getConvBeltTypeId()==CB_S_E) || (tileRobotCB->getConvBeltTypeId()==CB_NW_E) || (tileRobotCB->getConvBeltTypeId()==CB_W_E)){
            this->type=EM_CB_EAST;
        }
        //Others CB needs to be added
    }
    this->type=EM_NONE;
    return false;
}
