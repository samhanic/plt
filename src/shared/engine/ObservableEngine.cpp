#include "ObservableEngine.h"
#include "../state.h"
#include "../engine.h"
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

//mutable std::vector<Observer*> observers;

void const engine::ObservableEngine::registerObserver (ObserverEngine* o){
	observers.push_back(o);
}

void const engine::ObservableEngine::notifyUpdating (){
	for(auto observer : observers){
		observer->engineUpdating();
	}
}

void const engine::ObservableEngine::notifyUpdated(){
	for(auto observer : observers){
		observer->engineUpdated();
	}
}
