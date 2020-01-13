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

#include "../../src/client/client.h"
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
using namespace client;


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
		sf::RenderWindow window(sf::VideoMode(640 + 250, 640), "RobotIS");
		window.setFramerateLimit(25);
		
		Client myClient(window);
		myClient.run();

		return 0;
	}
	else {
		cout << "Fonction doesn't exist" << endl;
	}
	return 0;
}
