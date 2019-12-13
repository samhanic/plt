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

    generatePopulation();
    std::array<Action, 6> actions = tabPopulation[0].individual;
    
    for (int i = 0 ; i < 6 ; i++) {
        cout<<"ACTION : "<<tabPopulation[0].individual[i]<<endl;
    }
    
    engine.getMyState()->getPlayers()[nbRobot]->setRobotActions(actions);  

    return true;
}

void DeepAI::generatePopulation() {
    
    /* Must add bonus in the generation list if available */
    int choiceMatrix[5][2] = {{7, 4}, {7, 1}, {7, 2}, {7, 3}, {14, 14}};

    Action val;
    IndividualAI tempIndiv;

    for(int k = 0 ; k < 10 ; k++) {
        for(int i = 0 ; i < 3 ; i++) {
            int randomChoice = rand() % 4;

            val = static_cast<Action>(choiceMatrix[randomChoice][i * 2]);            
            tempIndiv.individual[i * 2] = val;
            val = static_cast<Action>(choiceMatrix[randomChoice][i * 2 + 1]);  
            tempIndiv.individual[i * 2 + 1] = val;
            tempIndiv.fitnessScore = rand() % 1000;
        }
        else return -1000+20*engine.getMyState()->nbRound;
    }
}

bool DeepAI::fusionActions () {
    return false;
}


/* Put the three best individuals at the top of population's tab */
bool DeepAI::sortTabPopulation() {
    IndividualAI firstIndiv , secondIndiv, thirdIndiv;

    for (int k = 0 ; k < 10 ; k++) {
        if (tabPopulation[k].fitnessScore > thirdIndiv.fitnessScore) {
            if (tabPopulation[k].fitnessScore > secondIndiv.fitnessScore) {
                if (tabPopulation[k].fitnessScore > firstIndiv.fitnessScore) {
                    thirdIndiv.fitnessScore = secondIndiv.fitnessScore;
                    thirdIndiv.individual = secondIndiv.individual;

                    secondIndiv.fitnessScore = firstIndiv.fitnessScore;
                    secondIndiv.individual = firstIndiv.individual;

                    firstIndiv.fitnessScore = tabPopulation[k].fitnessScore;
                    firstIndiv.individual = tabPopulation[k].individual;
                } else {
                    thirdIndiv.fitnessScore = secondIndiv.fitnessScore;
                    thirdIndiv.individual = secondIndiv.individual;

                    secondIndiv.fitnessScore = tabPopulation[k].fitnessScore;
                    secondIndiv.individual = tabPopulation[k].individual;
                }
            } else {
                thirdIndiv.fitnessScore = tabPopulation[k].fitnessScore;
                thirdIndiv.individual = tabPopulation[k].individual;
            }
        }  
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
