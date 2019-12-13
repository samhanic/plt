#include "../ai.h"
#include "../engine.h"
#include "../state.h"
#include "../../client/render.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <cmath>

using namespace ai;
using namespace engine;
using namespace state;
using namespace render;
using namespace std;

DeepAI::DeepAI (int nbRobot){
    this->nbRobot=nbRobot;
}

bool DeepAI::run (engine::Engine& engine){
    /*Verify that the game is not ended*/
    if (engine.getMyState()->getEndGame()) return false;
    return true;
}
/*
int evaluation (engine::Engine& engine){
    int eval;
    if (engine.getMyState()->getEndGame()){
        if (engine.getMyState()->getPlayers()[1]->getVisitedCheckpoints().size()==5){
            return 1000-20*engine.getMyState()->nbRound;
        }
        else return -1000+20*engine.getMyState()->nbRound;
    }
    else{
        return engine.getMyState()->getPlayers()[1]->getVisitedCheckpoints().size()*100;
        //To be refind maybe
    }
}

int DeepAI::min (engine::Engine& engine, int depth){
    cout<<"min calculus with depth"<<depth<<endl;
    int minValue = 10000;
    if (depth==0 || engine.getMyState()->getEndGame()==true){
        return evaluation(engine);
    }
    else{
        std::vector<state::Action> listActions;
        
    }
}*/

int DeepAI::evaluateRobot (engine::Engine& engine, int nbRobotTest){
    int evaluatedRobot;
    if (nbRobotTest!=-1) evaluatedRobot=nbRobotTest;
    else evaluatedRobot=nbRobot;
    int eval=0;
    if (engine.getMyState()->getEndGame()){
        if (engine.getMyState()->checkEndGame()==evaluatedRobot){
            return 10000; //You won!
        }
        else return -10000; //Other player won!
    }
    if (engine.getMyState()->getPlayers()[evaluatedRobot]->getLifeNumber()==0){
        return -10000; // You lost
    }

    //Evaluate the number of checkpoints you validated
    eval += engine.getMyState()->getPlayers()[evaluatedRobot]->getVisitedCheckpoints().size()*1000;

    //Evaluate the distance to the nearest checkpoint
    MapPathFinder mpf;
    state::Position nearest = mpf.nearestCP(*engine.getMyState(),evaluatedRobot);
    int difX = nearest.getX()-engine.getMyState()->getPlayers()[evaluatedRobot]->getPosition().getX();
    int difY = nearest.getY()-engine.getMyState()->getPlayers()[evaluatedRobot]->getPosition().getY();
    eval += 10*(std::sqrt(std::pow(difX,2)+std::pow(difY,2)));

    //evaluate the life
    eval+=engine.getMyState()->getPlayers()[evaluatedRobot]->getLifeNumber()*1000;
    eval+=engine.getMyState()->getPlayers()[evaluatedRobot]->getLifePoints()*200;

    if (nbRobotTest!=-1){
        uint robots = engine.getMyState()->getPlayers().size();
        for (size_t i=0; i<robots; ++i){
            if (i!=nbRobot){
                eval -= evaluateRobot(engine,i)/(2*robots);
            }
        }
    }
    return eval;
}

bool DeepAI::fusionActions (){
    
}

bool sortTabPopulation (){

}