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
    
    executeAction(1);
    //this->myState=std::shared_ptr<state>;
    // int actionNumber = 1;
    // Command actualAction = Command((*state.getPlayers()[0]),actionNumber);
    // actualAction.executeOrder(state);
    //std::copy(state, myState, state.begin());//myState = state;

    return true;
}

// void Engine::setMyState(const state::State& myState){
//     this->myState = myState;
// }
//Finally we do not use a setter and directly create an engine with a state

const std::shared_ptr<state::State>& Engine::getMyState() const{
    return myState;
}

void Engine::executeAction(int actionNumber){
    //state::Robot& player = myState.getPlayers()[0];
    std::vector<std::unique_ptr<Robot>>& players = myState->getPlayers();
    // std::unique_ptr<Robot>& player = players[actionNumber];
    Robot& playerTest = *players[actionNumber].get();

    cout << myState->getPlayers()[0]->getLifeNumber() <<" lifes" << endl;
    cout << myState->getPlayers()[0]->getOrientation() <<" orientation" << endl;
    //Command a besoin d'un state::Robot& player
    Command *actualAction = new Command(playerTest,actionNumber);
    delete actualAction;
    //Rotation actualAction = new Rotation(myState->getPlayers()[0],actionNumber);

    //vector<unique_ptr<Robot>> & refRobots = players;
    //Robot test = (*myState).getPlayers()[0];
    //Command actualAction = Command((*myState).getPlayers()[0]&,actionNumber);
    // Command actualAction = Command(myState.getPlayers()[0],actionNumber);
    // actualAction.executeOrder(myState);
}
