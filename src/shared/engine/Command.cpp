#include "Command.h"
#include "../state.h"

using namespace engine;
using namespace state;

Command::Command(state::Robot& player, int actionNumberInRound){
    this -> player = player;
    this -> actionNumberInRound = actionNumberInRound; 
}

Command::Command(){
    
}

void Command::executeOrder (state::Action action){
    
}