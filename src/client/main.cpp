#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>

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
		
		/* Prepares Observator to notifiy Engine if a player clicks on validate button */
		Observator renderObservator;
		myEngine.registerObservator(&renderObservator);

		// Observable stateObservator;

		/* Clean temp file to keep State history for rollback */
		std::ofstream ofs;
		ofs.open(FILE_NAME, std::ofstream::out | std::ofstream::trunc);
		ofs.close();
				
		/* IA will be the second Robot */
		ai::HeuristicAI aiRobot(1);
		
		ptrState->initRobot(ORANGE);

		sf::Clock clock;

		while (window.isOpen()){
			/* Rollback auto after 30 seconds */
			const unsigned int seconds = static_cast<unsigned int>(clock.getElapsedTime().asSeconds());
			if(seconds > 30) {
				while(myEngine.doRollback()) {
					statelay.refreshPlayers(*ptrState);		
					statelay.draw(*ptrState, window);
					sf::sleep(sf::seconds(2));
				}
				statelay.refreshPlayers(*ptrState);		
				statelay.draw(*ptrState, window);
				sf::sleep(sf::seconds(500));
			}


			statelay.eventManager(ptrState, window, statelay);

			/* Actions processed when all players have selected their actions */
			if (myEngine.checkRobotsActions()) {

				myEngine.saveInfoRollback();
				aiRobot.run(myEngine);
				aiRobot.processPlayersStats(myEngine);

				for (int i = 0 ; i < 6 ; i++) {
					if (!ptrState->getEndGame()) {
						/* Do action and check death */
						myEngine.executeAction(i);
						ptrState->checkEndGame();
						
						/* Refresh and display what needs to be */
						statelay.refreshPlayers(*ptrState);
						statelay.refreshEffects(*ptrState, i, 0);			
						statelay.draw(*ptrState, window);
						
						sf::sleep(sf::seconds(0.5));
					}
				}
				myEngine.endOfRound();

				statelay.initSurface(*ptrState);
				statelay.refreshEffects(*ptrState, 0, 0);
				statelay.draw(*ptrState, window);
			}
		} 	
		return 0;
	}
	else {
		cout << "Fonction doesn't exist" << endl;
	}
	return 0;
}
