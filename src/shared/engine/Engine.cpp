#include "../engine.h"
#include "../state.h"
#include "../client/render.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>

using namespace engine;
using namespace render;
using namespace state;
using namespace std;

#define FILE_NAME "state.txt"

Engine::Engine() {

}

Engine::Engine(std::shared_ptr<state::State> myState){
    this->myState=myState;
}

bool Engine::initEngine (std::string mapFileLocation){
    /* Creates a State and init map with MapFactory */
    State *state = new State();
    MapFactory mapFactory;
	state->initMap(mapFileLocation, mapFactory);
	std::shared_ptr<State> ptrState(state);
    this->myState = ptrState;
    
    /* Creates Robot and gives it empty action */
    state->initRobot(BLUE);
    std::array<Action, 6> initActionsRobot = {NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION};
    myState->getPlayers()[0]->setRobotActions(initActionsRobot);

    return true;
}

void Engine::clickOnValidate (int robotId, bool rollback) {

}

/* Empties actions of the Robot at the end of the round */
void Engine::endOfRound () {
    std::array<Action, 6> initActionsRobot = {NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION};
    myState->getPlayers()[0]->setRobotActions(initActionsRobot);
    
    /* Increments of round number and saves State for rollbacks */
    myState->roundNumber++;

    ofstream file; 
    file.open(FILE_NAME, ios::app);
    LightRollbackSave lightRBSave;

    for(unsigned int i = 0 ; i < myState->players.size() ; i++) {
        lightRBSave.rsRoundNumber = myState->roundNumber;
        lightRBSave.rsRobotId = myState->players[i]->getRobotId();
        lightRBSave.rsX = myState->players[i]->getPosition().getX();
        lightRBSave.rsY = myState->players[i]->getPosition().getY();
        lightRBSave.rsOrientation = myState->players[i]->getOrientation();
        lightRBSave.rsLifeNumber = myState->players[i]->getLifeNumber();
        lightRBSave.rsLifePoints = myState->players[i]->getLifePoints();

        file.write((char*)&lightRBSave, sizeof(lightRBSave));
    }
    file.close();
}

bool Engine::doRollback () {
    
    LightRollbackSave lightRBSave;

    ifstream file_obj; 
    file_obj.open(FILE_NAME, ios::in); 
    
    file_obj.read((char*)&lightRBSave, sizeof(lightRBSave));

    while (!file_obj.eof()) { 
        if ((lightRBSave.rsRoundNumber == myState->roundNumber) && (lightRBSave.rsRobotId == 0)) {
            cout<<"ROUND NUMBER : "<<lightRBSave.rsRoundNumber<<endl;
            cout<<"ROBOTID : "<<lightRBSave.rsRobotId<<endl;
            cout<<"X : "<<lightRBSave.rsX<<endl;
            cout<<"Y : "<<lightRBSave.rsY<<endl;
            cout<<"ORIENTATION : "<<lightRBSave.rsOrientation<<endl;
            cout<<"LIFENUMBER : "<<lightRBSave.rsLifeNumber<<endl;
            cout<<"LIFEPOINTS : "<<lightRBSave.rsLifePoints<<endl;

            if (myState->roundNumber > 1 ) {
                myState->roundNumber --;
            } else {
                return 0;
            }

            state::Position tempPos;
            tempPos.setX(lightRBSave.rsX);
            tempPos.setY(lightRBSave.rsY);

            myState->players[0]->setPosition(tempPos);
            myState->players[0]->setOrientation(lightRBSave.rsOrientation);
            myState->players[0]->setLifeNumber(lightRBSave.rsLifeNumber);
            myState->players[0]->setLifePoints(lightRBSave.rsLifePoints);
            cout<<"POISTION ACTUALIZED"<<endl;

            return 1;
        }
        file_obj.read((char*)&lightRBSave, sizeof(lightRBSave));
    }
    file_obj.close();
    return 1;
}


const std::shared_ptr<state::State>& Engine::getMyState() const{
    return myState;
}

void Engine::executeAction(int actionNumber) {
    //activeRobot=0;
    for(unsigned int i = 0 ; i <= 1 ; i++) {
        //int i = 0;
        Action processedAction = myState->getPlayers()[i]->getRobotActions()[actionNumber];

        if ((processedAction == ROTATION_CLK) || (processedAction == ROTATION_CCLK)) {
            Rotation myRotation(myState->getPlayers()[i]->getRobotId(), processedAction);
            myRotation.executeOrder(myState);
        }
        else if((processedAction == FORWARD) || (processedAction == BACKWARD)
        || (processedAction == LEFT) || (processedAction == RIGHT)) {
            Move myMove(myState->getPlayers()[i]->getRobotId(), processedAction);
            myMove.executeOrder(myState);
        } 
        else if (processedAction == BOOSTER) {
            Boost myBoost (myState->getPlayers()[i]->getRobotId());
            myBoost.executeOrder(myState);
        }
        else if (processedAction == state::ATTACK){
            Attack myAttack (myState->getPlayers()[i]->getRobotId());
            cout<<"Attacking robot"<<endl;
            myAttack.executeOrder(myState);
        }
        else{
            cout<<"This action ("<<processedAction<<") is not yet implemented"<<endl;
        }
        if (actionNumber==5) myState->getPlayers()[i]->setIsBoosted(0); 
        /* Checks if in hole or passed a checkpoint */
        checkHole();
        checkCheckPoint ();
        //Actions of the game on the robot
        EnvironmentMove *environment = new EnvironmentMove(0);
        environment->grabEMType(myState);
        environment->execute(myState);
        cout<<"action : "<<myState->getPlayers()[i]->getRobotActions()[actionNumber]<< "du robot : "<<i<<endl;
    }
 
}

/* Returns 1 if all actions are filled by players */
bool Engine::checkRobotsActions () {
    bool tempAction = 1;
    for (int i =0 ; i < 6 ; i++) {
        if (myState->getPlayers()[0]->getRobotActions()[0] == NO_ACTION) {
            tempAction = 0;
        }
    }
    return tempAction;
}

void Engine::checkHole () {
    Position myPos = myState->getPlayers()[0]->getPosition();
    int tileCodeOfRobotPos = myState->getMap()[myPos.getY()][myPos.getX()]->getTileCode();
    if (tileCodeOfRobotPos == 1)  {
        /* Losts one life */
        if (myState->getPlayers()[0]->getLifeNumber() > 0) {
            myState->getPlayers()[0]->setLifeNumber(myState->getPlayers()[0]->getLifeNumber()-1);
        }
        myState->getPlayers()[0]->setStatus(DEAD);
    }
}

void Engine::checkCheckPoint () {
    Position myPos = myState->getPlayers()[0]->getPosition();
    int tileCodeOfRobotPos = myState->getMap()[myPos.getY()][myPos.getX()]->getTileCode();
    bool tempIsVisited = false;
    if (tileCodeOfRobotPos >= 3 && tileCodeOfRobotPos <= 7) {
        /* Adds checkpoint to the visited checkpoint list if not already visited */
        std::vector<int> visitedCp = myState->getPlayers()[0]->getVisitedCheckpoints();
        for (unsigned int i = 0 ; i < visitedCp.size() ; i ++) {
            if (visitedCp[i] == tileCodeOfRobotPos - 2) {
                tempIsVisited = true;
            }
        }
        if (tempIsVisited == false) {
            visitedCp.push_back(tileCodeOfRobotPos - 2);
            myState->getPlayers()[0]->setVisitedCheckpoints(visitedCp);
        }
        // if (find(visitedCp.begin(), visitedCp.end(), 2) != visitedCp.end()) {
        //     visitedCp.push_back(tileCodeOfRobotPos - 2);
        //     myState->getPlayers()[0]->setVisitedCheckpoints(visitedCp);
        // }
    }
}

int Engine::getActiveRobot() const{
    return activeRobot;
}
