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

bool EnvironmentMove::execute (std::shared_ptr<state::State> theState){
    // Robot *robot = theState->getPlayers()[robotNumber];
    // MapTile *tileRobot = theState->getMap()[pos.getY()][pos.getX()].get();
    // if (tileRobot->getTypeId()==ROTATOR){
    //     Rotator *tileRobotRotator = static_cast<Rotator*>(tileRobot);
    //     if (tileRobotRotator->getRotatorTypeId()==ROT_CLK){
    //         Rotation environmentRotation = new Rotation(robotNumber,ROTATION_CLK);
    //         environmentRotation.executeOrder();
    //     }
    //     //To be added : CCLK
    // }
    // if (tileRobot->getTypeId()==CONVBELT){
    //     ConvBelt *tileRobotCB = static_cast<ConvBelt*>(tileRobot);
    //     if (robot->getOrientation()==NORTH){
    //         Move environmentMove = new Move(robotNumber,FORWARD);
    //     }
    //     //To be added : others directions
    // }
    // return true;
}

bool EnvironmentMove::grabEMType(std::shared_ptr<state::State> theState){
    // MapTile *tileRobot = theState->getMap()[pos.getY()][pos.getX()].get();
    // if (tileRobot->getTypeId()==ROTATOR){
    //     Rotator *tileRobotRotator = static_cast<Rotator*>(tileRobot);
    //     if(tileRobotRotator->getRotatorTypeId()==ROT_CLK){
    //         this->type=EM_ROTATION_CLK;
    //         return true;
    //     }
    //     else if (tileRobotRotator->getRotatorTypeId()==ROT_CCLK){
    //         this->type=EM_ROTATION_CCLK;
    //         return true;
    //     }
    // }
    // if (tileRobot->getTypeId()==CONVBELT){
    //     ConvBelt *tileRobotCB = static_cast<ConvBelt*>(tileRobot);
    //     if((tileRobotCB->getConvBeltTypeId()==CB_N_S) || (tileRobotCB->getConvBeltTypeId()==CB_E_S) || (tileRobotCB->getConvBeltTypeId()==CB_W_S)){
    //         this->type=EM_CB_SOUTH;
    //     }
    //     if((tileRobotCB->getConvBeltTypeId()==CB_N_E) || (tileRobotCB->getConvBeltTypeId()==CB_S_E) || (tileRobotCB->getConvBeltTypeId()==CB_NW_E) || (tileRobotCB->getConvBeltTypeId()==CB_W_E)){
    //         this->type=EM_CB_EAST;
    //     }
    //     //Others CB needs to be added
    // }
    // this->type=EM_NONE;
    // return false
}
