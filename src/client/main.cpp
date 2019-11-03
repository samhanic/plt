#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>


#include "../../src/shared/state.h"
#include "../../src/client/render.h"

#define MAP_FILE "../res/map.txt"

using namespace std;
using namespace render;
using namespace state;
//using namespace render;

int main(int argc,char* argv[])
{
    /* Gestion de la commande en entrée */
	if ( argc != 2 ) {
		cout<<"usage: "<< argv[0] <<" <command>\n";
	}
	string entry = argv[1];
	if (entry == "Hello") {
		cout << "Hello world" << endl;
	} else if (entry == "state") {
		system("make code-coverage");
	}
	else if (entry == "render") {
		/* Creation of a State and Window */
		State state;
		unsigned int width = state.getWidthMap(MAP_FILE);
        unsigned int height = state.getHeightMap(MAP_FILE);
		sf::RenderWindow window(sf::VideoMode(width * 64 + 400, height * 64), "RobotIS");
		window.setFramerateLimit(25);

		MapFactory mapFactory;
		state.initMap(MAP_FILE, mapFactory);
		state.initRobot(BLUE);


		StateLayer statelay(state, window);
		statelay.initSurface(state);

		while (window.isOpen()){
			sf::Event event;
			while (window.pollEvent(event)){
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			statelay.draw(window);
			window.display();
		}

		return 0;


	} else {
		cout << "Fonction doesn't exist" << endl;
	}
	return 0;
}
