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

#define MAP_FILE "../res/map.txt"

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
	} else if (entry == "state") {
		system("make code-coverage");
	} else if (entry == "render") {
		/* Creation of a State and Window */
		State state;
		int width = state.getMapWidth();
    	int height = state.getMapHeight();
		sf::RenderWindow window(sf::VideoMode(width * 64 + 250, height * 64), "RobotIS");
		window.setFramerateLimit(25);


		MapFactory mapFactory;
		state.initMap(MAP_FILE, mapFactory);
		state.initRobot(BLUE);
		state.initRobot(YELLOW);
		state.initRobot(RED);
		state.initRobot(PINK);
		state.initRobot(ORANGE);


		StateLayer statelay(state, window);
		statelay.initSurface(state);

		while (window.isOpen()){
			sf::Event event;
			while (window.pollEvent(event)){
				if (event.type == sf::Event::Closed)
					window.close();
				statelay.clickManager(state, event);
			}
			window.clear();
			statelay.draw(state, window);
			window.display();
		}
		return 0;

	} else if (entry== "engine") {
		/* Creates Engine that creates State */
		Engine myEngine;
		myEngine.initEngine();
		myEngine.executeAction(0);
		const std::shared_ptr<state::State> ptrState = myEngine.getMyState();

		/* Displays a sf::Window with the correct size and frame rate */
		unsigned int width = ptrState->getMapWidth();
   		unsigned int height = ptrState->getMapHeight();
		sf::RenderWindow window(sf::VideoMode(width * 64 + 250, height * 64), "RobotIS");
		window.setFramerateLimit(25);

		/* Creates a StateLayer that will construct and display five sub-layers */
		StateLayer statelay(*ptrState, window);
		statelay.initSurface(*ptrState);

		while (window.isOpen()){
			/* Click management in loop */
			sf::Event event;
			while (window.pollEvent(event)){
				if (event.type == sf::Event::Closed)
					window.close();
				statelay.clickManager(*ptrState, event);
			}
			window.clear();
			statelay.draw(*ptrState, window);

			/* Actions processed when all players have selected their actions */
			if (myEngine.checkRobotsActions()) {
				for (int i = 0 ; i < 6 ; i++) {
					if (!ptrState->getEndGame()) {
						myEngine.executeAction(i);
						statelay.refreshPlayers(*ptrState);
						
						ptrState->checkEndGame();
						
						statelay.draw(*ptrState, window);
						sf::sleep(sf::seconds(0.3));
					}
				}
				
				myEngine.endOfRound();
				statelay.initSurface(*ptrState);
			}
		} 	
		return 0;
	} else {
		cout << "Fonction doesn't exist" << endl;
	}
	return 0;
}
