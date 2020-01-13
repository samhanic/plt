#include "../state.h"
#include <iostream>

using namespace state;
using namespace std;

void Observable::registerObserver (IObserver* observer){
	observers.push_back(observer);
}

void Observable::notifyObservers (const StateEvent& e, State& state){
	for(auto observer : observers){
		cout<<"Render notified"<<endl;
		observer->stateChanged(e, state);
		
	}
}
