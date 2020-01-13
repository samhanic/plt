#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>
#include <SFML/System.hpp>
#include <functional>

#include "../../src/shared/state.h"
#include "../../src/client/render.h"
#include "../../src/shared/engine.h"
#include "../../src/shared/ai.h"

#define MAP_FILE "../res/map.txt"
#define FILE_NAME "state.txt"

using namespace std;
using namespace render;
using namespace state;
using namespace engine;


void runRender (const std::shared_ptr<state::State> myState, sf::RenderWindow& myWindow, StateLayer& myStateLayer) {
    myWindow.setActive(true);
    while (myWindow.isOpen()) {
        myStateLayer.initSurface(*myState);
        myStateLayer.refreshPlayers(*myState);
        myStateLayer.refreshEffects(*myState, 0, 0);			
        myStateLayer.draw(*myState, myWindow);
        myWindow.display();
    }			
}



int main(int argc,char* argv[])
{
    /* Gestion de la commande en entrée */
	if ( argc != 2 ) {
		cout<<"usage: "<< argv[0] <<" <command>\n";
	}
	string entry = argv[1];
	if (entry == "hello") {
		cout << "Hello world" << endl;
	}
	else if (entry == "state") {
		system("make code-coverage");
	}
	else if (entry == "render") {
		cout << "use command 'deep_ai' to execute 'render'" << endl;
	}
	else if (entry== "engine") {
		cout << "use command 'deep_ai' to execute 'engine'" << endl;
	}
	else if(entry== "random_ai"){		
		cout << "use command 'deep_ai' to execute 'random_ai'" << endl;
	}
	else if(entry== "heuristic_ai"){		
		cout << "use command 'deep_ai' to execute 'heuristic_ai'" << endl;
	}
	else if(entry== "rollback"){	
		cout << "use command 'deep_ai' to execute 'rollback'" << endl;	
	}
	else if(entry== "deep_ai"){
		cout << "use command 'deep_ai' to execute 'deep_ai'" << endl;
	}
	else if(entry== "thread"){
		/* INITIALIZATION */
		/* Creates Engine that creates State */
		Engine myEngine;
		myEngine.initEngine(MAP_FILE);
		const std::shared_ptr<state::State> ptrState = myEngine.getMyState();

		/* Displays a sf::Window with the correct size and frame rate */
		unsigned int width = ptrState->getMapWidth();
   		unsigned int height = ptrState->getMapHeight();
		sf::RenderWindow window(sf::VideoMode(width * 64 + 250, height * 64), "RobotIS");
		window.setFramerateLimit(25);

		/* Creates a StateLayer that will construct and display five sub-layers */
		StateLayer statelay(*ptrState, window);
		statelay.initSurface(*ptrState);
		
		// /* Prepares Observator to notifiy Engine if a player clicks on validate button */
		// Observator renderObservator;
		// myEngine.registerObservator(&renderObservator);
		// // Observable stateObservator;

		
				
		/* IA will be the second Robot */
		ai::HeuristicAI aiRobot(1);
		ptrState->initRobot(ORANGE);



		// sf::Thread myThread(std::bind(&render::StateLayer::runRender, &ptrState, &window, &statelay));
    	// myThread.launch();
		//thread funcTest1(render::StateLayer::runRender);
		// window.setActive(false);
		// sf::Thread thread(std::bind(&runRender, &ptrState, &window, &statelay));
    	// thread.launch();


		while (window.isOpen()){
			statelay.eventManager(ptrState, window, statelay);

			/* Actions processed when all players have selected their actions */
			if (myEngine.checkRobotsActions()) {

				aiRobot.run(myEngine);

				for (int i = 0 ; i < 6 ; i++) {
					if (!ptrState->getEndGame()) {
						/* Do action and check death */
						myEngine.executeAction(i);
						ptrState->checkEndGame();
						
						/* Refresh and display what needs to be */
						statelay.runRender(ptrState, window, statelay);
							
						sf::sleep(sf::seconds(0.5));
					}
				}
				myEngine.endOfRound();
				statelay.runRender(ptrState, window, statelay);
			}
		} 	
		return 0;
	}
	else {
		cout << "Fonction doesn't exist" << endl;
	}
	return 0;
}
