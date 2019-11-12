#include "Command.h"
#include "../state.h"
#include "../engine.h"
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Command::Command(state::Robot& player, int actionNumberInRound){
    //this -> player = player;
    this -> actionNumberInRound = actionNumberInRound; 
}

Command::Command(){
    
}

void Command::setPlayer(std::unique_ptr<state::Robot>& player){
    // this->player=player;
}

int Command::getActionNumberInRound() const{
    return actionNumberInRound;
}

void Command::setActionNumberInRound(int actionNumberInRound){
    this->actionNumberInRound = actionNumberInRound;
}

CommandPriority Command::getPriority() const{
    return priority;
}

void Command::setPriority(CommandPriority priority){
    this->priority = priority;
}

bool Command::executeOrder (state::State& myState){
    return 0; //If this functions executes heres,
    //there is a problem because all executeOrders should be executed in subclasses
}

