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

DeepAI::DeepAI (int nbRobot){
    this->nbRobot=nbRobot;
}

bool DeepAI::run (engine::Engine& engine){
    /*Verify that the game is not ended*/
    if (engine.getMyState()->getEndGame()) return false;

    
    //engine.getMyState()->getPlayers()[nbRobot]->setRobotActions(tabPopulation[0]);  
    return true;
}

void DeepAI::generatePopulation() {
    
    /* Must add bonus in the generation list if available */
    int choiceMatrix[5][2] = {{7, 4}, {7, 1}, {7, 2}, {7, 3}, {14, 14}};


    for(int k = 0 ; k < 10 ; k++) {
        IndividualAI tempIndiv;
        this->tabPopulation[k] = tempIndiv;
//        tempIndiv = this->tabPopulation[k];

        for(int i = 0 ; i < 3 ; i++) {
            int randomChoice = rand() % 4;
            tempIndiv.individual[i * 2] = state::FORWARD;
            tempIndiv.individual[i * 2 + 1] = state::FORWARD;
            tempIndiv.fitnessScore = 0;
        }
    }
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
