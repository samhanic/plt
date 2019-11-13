#include "../render.h"
#include "../../shared/state.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;
using namespace render;
using namespace state;


void Observator::registerObservator (Observator* observator){
	observers.push_back(observator);
}

void Observator::notifyObservators (state::Robot& myRobot, bool rollback){
	
	for(auto observer : observers){
		
		//observer->actionsChanged(myRobot,rollback);
	}
}
