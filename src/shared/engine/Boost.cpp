#include "Boost.h"
#include "../state.h"
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Boost::Boost(int robotNumber){
    this->robotNumber=robotNumber;
}


bool Boost::executeOrder (std::shared_ptr<state::State> theState){
    int boost = theState->getPlayers()[robotNumber]->getIsBoosted();
    theState->getPlayers()[robotNumber]->setIsBoosted(boost+1);
    //cout<<"your boost in now "<<boost+1<<endl;
    return true;
}