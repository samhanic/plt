#include <iostream>
#include <unistd.h>
#include <SFML/Graphics.hpp>
#include <thread>
#include <pthread.h>
#include <unistd.h>

#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/shared/ai.h"
#include "../client.h"
#include "../render.h"

#define MAP_FILE "../res/map.txt"

using namespace state;
using namespace engine;
using namespace render;
using namespace std;
using namespace ai;
using namespace client;


void thread_moteurclient(void* ptr, int i){
	Engine* ptr_moteur=(Engine*)ptr;
	usleep(1000);
	//ptr_moteur->update();
	ptr_moteur->executeAction(i);
	ptr_moteur->getMyState()->checkEndGame();
}

Client::Client (sf::RenderWindow& window): window(window) {

	myEngine.initEngine(MAP_FILE);
	const std::shared_ptr<state::State> ptrState = myEngine.getMyState();

	StateLayer statelay(*ptrState, window);
	statelay.initSurface(*ptrState);
}


void Client::run (){
	const std::shared_ptr<state::State> ptrState = myEngine.getMyState();

	StateLayer statelay(*ptrState, window);
	statelay.initSurface(*ptrState);


	StateLayer* ptr_stateLayer = &statelay;
	myEngine.getMyState()->registerObserver(ptr_stateLayer);


	ai::HeuristicAI aiRobot(1);
	ptrState->initRobot(ORANGE);
    //std::thread engineThread(engineProcess);
	while (window.isOpen()){
		statelay.eventManager(ptrState, window, statelay);

		/* Actions processed when all players have selected their actions */
		if (myEngine.checkRobotsActions()) {

			aiRobot.run(myEngine);
            for (int i = 0 ; i < 6 ; i++) {
                if (!myEngine.getMyState()->getEndGame()) {
					std::thread th(thread_moteurclient,&myEngine,i);
					cout<<"Thread created!"<<endl;
					th.join();
                    
                    /* Refresh and display what needs to be */			
                    StateEvent majDisponibilite(ALL_CHANGED);
                    myEngine.getMyState()->notifyObservers(majDisponibilite, *myEngine.getMyState());
                        
                    sf::sleep(sf::seconds(0.5));
                }
            }
            myEngine.endOfRound();		
		}
	}
}
