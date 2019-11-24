#include "../render.h"
#include "../../shared/state.h"
#include "../../shared/engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>

using namespace std;
using namespace render;
using namespace state;
using namespace engine;


void Observator::registerObservator (Observator* observer){
	observers.push_back(observer);
}

void Observator::notifyObservators (int robotId, bool rollback){
	
	for(auto observer : observers){		
		//observer->clickOnValidate(robotId, rollback);
		observer->notifyObservators(robotId, rollback);
		cout<<"Engine notified"<<endl;
	}
}
