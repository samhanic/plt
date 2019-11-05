#include "Engine.h"
#include "../state.h"

using namespace engine;
using namespace state;

Engine::Engine() {

}

const state::State& Engine::getMyState()const{
    return myState;
}

void Engine::executeAction(int actionNumber){
    
}
