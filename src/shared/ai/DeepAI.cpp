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
#include <list>
#include <string>
#include <algorithm>

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
    evaluatePopulation(engine);

    std::array<Action, 6> actions = tabPopulation[0].individual;

    for (int i = 0 ; i < 6 ; i++) {
<<<<<<< HEAD
        cout<<"ACTION : "<<tabPopulation[0].individual[i]<<endl;
        //tabPopulation[0].individual[i] = state::FORWARD;
=======
        
        //tabPopulation[0].individual[i] = state::FORWARD;
        cout<<"1st action : "<<tabPopulation[0].individual[i]<<endl;
        cout<<"Fitness score of this action is "<<tabPopulation[i].fitnessScore<<endl;
>>>>>>> master
    }
    
    engine.getMyState()->getPlayers()[nbRobot]->setRobotActions(actions);  

    return true;
}

void DeepAI::generatePopulation() {
    
    /* Must add bonus in the generation list if available */
    int choiceMatrix[7][2] = {{7, 4}, {7, 1}, {7, 2}, {7, 3}, {14, 14}, {6,1}, {5, 1}};

    Action val;
    IndividualAI tempIndiv;

    for(int k = 0 ; k < 10 ; k++) {
        for(int i = 0 ; i < 3 ; i++) {
            int randomChoice = rand() % 6;

            val = static_cast<Action>(choiceMatrix[randomChoice][i * 2]);            
            tempIndiv.individual[i * 2] = val;
            val = static_cast<Action>(choiceMatrix[randomChoice][i * 2 + 1]);  
            tempIndiv.individual[i * 2 + 1] = val;
            //tempIndiv.fitnessScore = rand() % 1000;
        }
        tabPopulation[k]  = tempIndiv;
    }
}

/* Fusion genes of two individuals to improve result */
bool DeepAI::fusionActions () {


    return 1;
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

    tabPopulation[0] = firstIndiv;
    tabPopulation[1] = secondIndiv;
    tabPopulation[2] = thirdIndiv;

    return 1;
}

int DeepAI::evaluateRobot (engine::Engine& engine, int nbRobotTest){
    uint evaluatedRobot;
    if (nbRobotTest!=-1) evaluatedRobot=(uint) nbRobotTest;
    else evaluatedRobot=(uint) nbRobot;
    int eval=1000;
    if (engine.getMyState()->getEndGame()){
        if (engine.getMyState()->checkEndGame() == (int) evaluatedRobot){
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

    // if (nbRobotTest!=-1){
    //     uint robots = engine.getMyState()->getPlayers().size();
    //     for (size_t i=0; i<robots; ++i){
    //         if (i!=evaluatedRobot){
    //             eval -= evaluateRobot(engine,i)/(2*robots);
    //         }
    //     }
    // }
    cout<<"Evaluation at"<<eval<<"points."<<endl;
    return eval;
}

bool DeepAI::fusionActions (){
    return false;
}

bool DeepAI::sortTabPopulation (){
    return false;
}

bool DeepAI::evaluatePopulation (engine::Engine& engine){
    //for (size_t i=0;i<tabPopulation.size();++i){
        int i=0;
        //1. Save the state
        std::shared_ptr<state::State> savedstate = engine.getMyState();
        //engine.saveInfoRollback();
        //2. Fill the player actions
        engine.getMyState()->getPlayers()[nbRobot]->setRobotActions(tabPopulation[i].individual);
        //3. Fill the others players actions
        for (size_t j=0;j<engine.getMyState()->getPlayers().size();++j){
            if (nbRobot!=(int) j){
                ai::HeuristicAI aiRobot(j);
                aiRobot.run(engine);
            }
        }
        //4. Execute the 6 actions
        for (size_t j = 0 ; j < 6 ; ++j) {
            if (!engine.getMyState()->getEndGame()) {
                /* Do action and check death */
                engine.executeAction(j);
                engine.getMyState()->checkEndGame();
            }
        }
        //5. Evaluate the robot
        tabPopulation[i].fitnessScore=evaluateRobot(engine, nbRobot);
        //6. Rollback
        engine.setMyState(savedstate);
        //engine.doRollback();

    //}
    return true;
}