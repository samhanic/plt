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

    for (int i = 0 ; i < 10 ; i++) {
        generatePopulation();
        evaluatePopulation(engine);
        sortTabPopulation();
    }

    std::array<Action, 6> actions = tabPopulation[0].individual;

    //cout<<"POPULATION : "<<endl;
    for (int j=0; j<1000; ++j){
        cout<<"a :"<<tabPopulation[j].individual[0]<<" , b:"<<tabPopulation[j].individual[1]<<" , c:"<<tabPopulation[j].individual[2]<<" , d:"<<tabPopulation[j].individual[j]<<" , e:"<<tabPopulation[j].individual[4]<<" , f:"<<tabPopulation[j].individual[5]<<" FITNESS : "<<tabPopulation[j].fitnessScore<<endl;
    }
    for (int i = 0 ; i < 6 ; i++) {      
        //cout<<"ACTION : "<<i<<" ; "<<(int) tabPopulation[0].individual[i]<<endl;
    }
    
    engine.getMyState()->getPlayers()[nbRobot]->setRobotActions(actions);  

    return true;
}

void DeepAI::generatePopulation() {
    
    /* Must add bonus in the generation list if available */
    int choiceMatrix[9][2] = {{7, 4}, {7, 1}, {7, 2}, {7, 3}, {14, 14}, {6,1}, {5, 1}, {1, 1}, {2, 2}};

    Action val;
    IndividualAI tempIndiv;

    for(int k = 3 ; k < 1000 ; k++) {
        //cout<<"INDIVIDUAL NUMBER : "<<k<<endl;
        tempIndiv.fitnessScore = tabPopulation[k].fitnessScore;
        for(int i = 0 ; i < 3 ; i++) {
            int randomChoice = rand() % 7;

            val = static_cast<Action>(choiceMatrix[randomChoice][i * 2]);            
            tempIndiv.individual[i * 2] = val;
            val = static_cast<Action>(choiceMatrix[randomChoice][i * 2 + 1]);  
            tempIndiv.individual[i * 2 + 1] = val;
            //tempIndiv.fitnessScore = rand() % 1000;
            ////cout<<"Action list :"<<tempIndiv.individual[i * 2]<<"|"<<tempIndiv.individual[i * 2 + 1]<<endl;
        }
        tabPopulation[k]  = tempIndiv;
    }
}

/* Fusion genes of two individuals to improve result */
bool DeepAI::fusionActions () {
    int indexTab[3] = {0, 2, 4};
    int randGene = rand() % 2;
    
    tabPopulation[3].individual[(int)indexTab[randGene]] = tabPopulation[0].individual[indexTab[randGene]];
    tabPopulation[4].individual[indexTab[randGene] + 1] = tabPopulation[0].individual[indexTab[randGene]+1];

    return 1;
}


/* Put the three best individuals at the top of population's tab */
bool DeepAI::sortTabPopulation() {
    IndividualAI firstIndiv , secondIndiv, thirdIndiv;

    for (int k = 5 ; k < 1000 ; k++) {
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
    int robotWinner = engine.getMyState()->checkEndGame();
    if (engine.getMyState()->getEndGame()){
        cout<<"In evaluateRobot : game ended"<<endl;
        if (robotWinner == (int) evaluatedRobot){
            return 50000; //You won!
        }
        else return -50000; //Other player won!
    }
    if (engine.getMyState()->getPlayers()[evaluatedRobot]->getLifeNumber()==0){
        return -50000; // You lost
    }

    //Evaluate the number of checkpoints you validated
    eval += engine.getMyState()->getPlayers()[evaluatedRobot]->getVisitedCheckpoints().size()*1000;

    //Evaluate the distance to the nearest checkpoint
    MapPathFinder mpf;
    state::Position nearest = mpf.nearestCP(*engine.getMyState(),evaluatedRobot);
    int difX = nearest.getX()-engine.getMyState()->getPlayers()[evaluatedRobot]->getPosition().getX();
    int difY = nearest.getY()-engine.getMyState()->getPlayers()[evaluatedRobot]->getPosition().getY();
    eval += 100*(std::sqrt(std::pow(difX,2)+std::pow(difY,2)));

    //evaluate the life
    eval+=engine.getMyState()->getPlayers()[evaluatedRobot]->getLifeNumber()*1000;
    eval+=engine.getMyState()->getPlayers()[evaluatedRobot]->getLifePoints()*200;

    //cout<<"Evaluation at"<<eval<<"points."<<endl;
    return eval;
}

bool DeepAI::evaluatePopulation (engine::Engine& engine){
    
    /* Save current state before rollback */
    std::vector<LightRollbackSave> tabRollBack;
    LightRollbackSave tempRollBack;
    
    std::array<Action, 6> tempActionOthers = engine.getMyState()->getPlayers()[0]->getRobotActions();
    std::vector<int> tempCPs = engine.getMyState()->getPlayers()[0]->getVisitedCheckpoints();

    for (unsigned int i = 0 ; i < engine.getMyState()->getPlayers().size() ; i++) {
        tempRollBack.rsLifeNumber = engine.getMyState()->getPlayers()[i]->getLifeNumber();
        tempRollBack.rsLifePoints = engine.getMyState()->getPlayers()[i]->getLifePoints();
        tempRollBack.rsOrientation = engine.getMyState()->getPlayers()[i]->getOrientation();
        tempRollBack.rsX = engine.getMyState()->getPlayers()[i]->getPosition().getX();
        tempRollBack.rsY = engine.getMyState()->getPlayers()[i]->getPosition().getY();
        tempRollBack.rsCP = engine.getMyState()->getPlayers()[i]->getVisitedCheckpoints();

        tabRollBack.push_back(tempRollBack);
        //cout<<"SAVE ROBOT " << engine.getMyState()->getPlayers()[i]->getRobotId() << endl;
    }

    //Give the others player heuristic ai
    ai::HeuristicAI aiRobot(0);
    aiRobot.processPlayersStats(engine);
    
    // /* Loop to test each individual */
    for (unsigned int i = 0 ; i  < tabPopulation.size() ; ++i) {
        aiRobot.run(engine);
        /* Fill players actions */      
        engine.getMyState()->getPlayers()[1]->setRobotActions(tabPopulation[i].individual);

        /* Execute actions */
        for (int j = 0 ; j < 6 ; j++) {
		 	if (!engine.getMyState()->getEndGame()) {
			    /* Do action and check death */
                ////cout<<"Action runned (nb "<<i<<" ) is "<<engine.getMyState()->getPlayers()[1]->getRobotActions()[i]<<endl;
		 		engine.executeAction(j);
		 		engine.getMyState()->checkEndGame();
            }
		}
		engine.endOfRound();
		

        /* Evaluate */
        tabPopulation[i].fitnessScore = evaluateRobot(engine, 1);
        //cout<<"Actions evaluated at "<<tabPopulation[i].fitnessScore<<endl;
        //cout<<"These actions are a :"<<tabPopulation[i].individual[0]<<" , b:"<<tabPopulation[i].individual[1]<<" , c:"<<tabPopulation[i].individual[2]<<" , d:"<<tabPopulation[i].individual[3]<<" , e:"<<tabPopulation[i].individual[4]<<" , f:"<<tabPopulation[i].individual[5]<<endl;

        
        /* Rollback */
        state::Position tempPos;
        for (unsigned int j = 0 ; j < engine.getMyState()->getPlayers().size() ; j++) {
            engine.getMyState()->getPlayers()[j]->setLifeNumber(tabRollBack[j].rsLifeNumber);
            engine.getMyState()->getPlayers()[j]->setLifePoints(tabRollBack[j].rsLifePoints);
            engine.getMyState()->getPlayers()[j]->setOrientation(tabRollBack[j].rsOrientation);
            engine.getMyState()->getPlayers()[j]->setVisitedCheckpoints(tabRollBack[j].rsCP);
            tempPos.setX(tabRollBack[j].rsX);
            tempPos.setY(tabRollBack[j].rsY);
            engine.getMyState()->getPlayers()[j]->setPosition(tempPos);
        }
        engine.getMyState()->getPlayers()[0]->setRobotActions(tempActionOthers);
        engine.getMyState()->getPlayers()[0]->setVisitedCheckpoints(tempCPs);
    }
    return true;
}