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

HeuristicAI::HeuristicAI(int nbRobot) {
    this->nbRobot = nbRobot;
}

bool HeuristicAI::run(engine::Engine& engine){
    /*Verify that the robot is still alive*/
    if(engine.getMyState()->getPlayers()[nbRobot]->getStatus()==FINAL_DEAD)
        return false;
    if(engine.getMyState()->getPlayers()[nbRobot]->getStatus()==STUNNED)
        return false;

    cout<<"Choosing 6 actions"<<endl;
    
    std::array<Action, 6> actions;
    unsigned int actionNumber = 0;
    for (unsigned int i = 0 ; i < playersWinProb.size() ; i++) {
        /* If player in the range, IA shoots */
        if (playersWinProb[i] > 60 ){
            actions[0]=Action::ATTACK;
            actionNumber = 1;
        }
    }
    if (engine.getMyState()->getPlayers()[nbRobot]->getLifePoints()<=2){
        if (engine.getMyState()->getPlayers()[nbRobot]->getBonusOwned()[0]){
            actions[actionNumber]=B_HEAL;
            actionNumber+=1;
        }
        else if(engine.getMyState()->getPlayers()[nbRobot]->getBonusOwned()[2]){
            actions[actionNumber]=B_SHIELD;
            actionNumber+=1;
        }
    }
    MapPathFinder mpf;
    std::array<Action, 6> actionsMove = mpf.pathToNearestCp(*engine.getMyState(),nbRobot);
    int i=0;
    while (actionNumber<6){
        actions[actionNumber]=actionsMove[i];
        ++actionNumber;
        ++i;
    }

    engine.getMyState()->getPlayers()[nbRobot]->setRobotActions(actions);  
    return true;
}

void HeuristicAI::processPlayersStats(engine::Engine& engine){
    /* Gives a win probabilites to each player in function of life, hp, and visited checkpoints */
    int nbLife = 0;
    int nbHP = 0;
    int nbVisitedCp = 0;

    int cpNumber = 5;

    float winProbaPurcentage = 0;

    std::vector<float> myvector (engine.getMyState()->getPlayers().size());
  
    for (unsigned int i = 0 ; i < engine.getMyState()->getPlayers().size() ; i++) {
        nbLife = engine.getMyState()->getPlayers()[i]->getLifeNumber();
        nbHP = engine.getMyState()->getPlayers()[i]->getLifePoints();
        nbVisitedCp =  engine.getMyState()->getPlayers()[i]->getVisitedCheckpoints().size();

        if (nbVisitedCp > 0) {
            winProbaPurcentage = nbVisitedCp / cpNumber;
            if (nbLife == 2) {
                winProbaPurcentage = winProbaPurcentage - 10;
            } else if (nbLife == 1) {
                winProbaPurcentage = winProbaPurcentage - 20;
            }
            if (nbHP <= 2) {
                winProbaPurcentage = winProbaPurcentage - 30;
            }
        }

        if (winProbaPurcentage < 0) {
            winProbaPurcentage = 0;
        }
        
        myvector[i] = winProbaPurcentage;
    }
    this->playersWinProb = myvector;
}