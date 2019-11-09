#include "../engine.h"
#include "../state.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

using namespace engine;
using namespace state;
using namespace std;

Engine::Engine() {

}

bool Engine::initEngine (){
    State *state = new State();
    MapFactory mapFactory;
	state->initMap("../res/map.txt", mapFactory);
	state->initRobot(BLUE);
    std::shared_ptr<State> ptrState(state);
    this->myState = ptrState;

    std::array<Action, 6> initActionsRobot = {NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION};
    myState->getPlayers()[0]->setRobotActions(initActionsRobot);

    //executeAction(1);
    //this->myState=std::shared_ptr<state>;
    // int actionNumber = 1;
    // Command actualAction = Command((*state.getPlayers()[0]),actionNumber);
    // actualAction.executeOrder(state);
    //std::copy(state, myState, state.begin());//myState = state;

    return true;
}

void Engine::endOfRound () {
    std::array<Action, 6> initActionsRobot = {NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION, NO_ACTION};
    myState->getPlayers()[0]->setRobotActions(initActionsRobot);
}

const std::shared_ptr<state::State>& Engine::getMyState() const{
    return myState;
}

void Engine::executeAction(int actionNumber) {
    Action processedAction = myState->getPlayers()[0]->getRobotActions()[actionNumber];
    if ((processedAction == ROTATION_CLK) || (processedAction == ROTATION_CCLK)) {
        Rotation myRotation(myState->getPlayers()[0]->getRobotId(), processedAction);
        myRotation.executeOrder(myState);
    }
    else if((processedAction == FORWARD) || (processedAction == BACKWARD)
    || (processedAction == LEFT) || (processedAction == RIGHT)) {
        Move myMove(myState->getPlayers()[0]->getRobotId(), processedAction);
        myMove.executeOrder(myState);
    } 
    else if (processedAction == BOOSTER) {
        myState->getPlayers()[0]->setIsBoosted(1); // A CHANGER
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