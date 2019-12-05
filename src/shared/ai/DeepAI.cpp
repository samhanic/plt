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

bool DeepAI::run (engine::Engine& moteur){
    return true;
}

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
}

int DeepAI::max (engine::Engine& engine, int depth){
    return 0;
}