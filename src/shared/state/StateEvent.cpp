#include "../state.h"
#include <iostream>

using namespace state;
using namespace std;
 
StateEvent::StateEvent (StateEventID se):stateEventID(se){
}

void StateEvent::setStateEventID(StateEventID newID){
	stateEventID=newID;
}
