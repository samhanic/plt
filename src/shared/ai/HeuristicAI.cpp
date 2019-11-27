#include "../ai.h"
#include "../engine.h"
#include "../state.h"
#include "../../client/render.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

using namespace ai;
using namespace engine;
using namespace state;
using namespace render;
using namespace std;

HeuristicAI::HeuristicAI(int nbRobot){
    this->nbRobot=nbRobot;
}

bool HeuristicAI::run(engine::Engine& engine){
    /*Verify that the robot is still alive*/
    if(engine.getMyState()->getPlayers()[nbRobot]->getStatus()==FINAL_DEAD) return false;
    if(engine.getMyState()->getPlayers()[nbRobot]->getStatus()==STUNNED) return false;

    cout<<"Choosing 6 actions randomly to run"<<endl;
    std::array<Action, 6> actions;
    int randomNumber;
    
    for (int i=0 ; i<6 ; ++i) {
        actions[i] = FORWARD;
    }
    
    engine.getMyState()->getPlayers()[nbRobot]->setRobotActions(actions);  
    return true;
}

void HeuristicAI::processPlayersStats(engine::Engine& engine){
    
    cout<<"Choosing 6 actions randomly to run"<<endl;
    std::array<Action, 6> actions;
    int randomNumber;
    
    for (int i=0 ; i<6 ; ++i) {
        actions[i] = FORWARD;
    }
    
    engine.getMyState()->getPlayers()[nbRobot]->setRobotActions(actions);  
}
