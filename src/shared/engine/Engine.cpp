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

// void Engine::setMyState(const state::State& myState){
//     this->myState = myState;
// }
//Finally we do not use a setter and directly create an engine with a state

const std::shared_ptr<state::State>& Engine::getMyState() const{
    return myState;
}

void Engine::executeAction(int actionNumber){
    Action processedAction = myState->getPlayers()[0]->getRobotActions()[actionNumber];
    cout<<processedAction << " is executing" <<endl;
    if (processedAction == ROTATION_CLK or processedAction == ROTATION_CCLK) {
        int actionRobot = static_cast<Action>(processedAction);
        Rotation myRotation(myState->getPlayers()[0]->getRobotId(), actionRobot);
        myRotation.executeOrder(myState);
    }
    else if(processedAction == FORWARD or processedAction == BACKWARD){
        int actionRobot = static_cast<Action>(processedAction);
        Move myMove(myState->getPlayers()[0]->getRobotId(), actionRobot);
        myMove.executeOrder(myState);
    }
}

bool Engine::checkRobotsActions () {
    bool tempAction = 1;
    for (int i =0 ; i < 6 ; i++) {
        if (myState->getPlayers()[0]->getRobotActions()[0] == NO_ACTION) {
            tempAction = 0;
        }
    }
    return tempAction;

}