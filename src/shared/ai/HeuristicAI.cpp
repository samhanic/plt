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

    cout<<"Choosing 6 actions go to the next checkpoint"<<endl;
    int randomNumber;
    
    MapPathFinder mpf;
    engine.getMyState()->getPlayers()[nbRobot]->setRobotActions(mpf.pathToNearestCp(*engine.getMyState(),nbRobot));  
    return true;
}

void HeuristicAI::processPlayersStats(engine::Engine& engine){
    
    cout<<"Choosing 6 actions"<<endl;
    MapPathFinder mpf;
    
    engine.getMyState()->getPlayers()[nbRobot]->setRobotActions(mpf.pathToNearestCp(*engine.getMyState(),nbRobot));  
}
