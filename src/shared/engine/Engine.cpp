#include "../engine.h"
#include "../state.h"
#include "../client/render.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

using namespace engine;
using namespace render;
using namespace state;
using namespace std;

Engine::Engine() {

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
}

const std::shared_ptr<state::State>& Engine::getMyState() const{
    return myState;
}

void Engine::executeAction(int actionNumber) {
    // ADD Robot SELECTOR
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
        else{
            cout<<"This action ("<<processedAction<<") is not yet implemented"<<endl;
        }
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
