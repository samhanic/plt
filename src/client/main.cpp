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
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						int idCommandClicked = -1;
						
						if ((event.mouseButton.x > 690) && (event.mouseButton.x < 730)
						&& (event.mouseButton.y > 100) && (event.mouseButton.y < 140)) {
							idCommandClicked = 0;
						}
						
						/* Une zone de commande a été cliquée */
						if (idCommandClicked != -1) {
							/* On regarde sur quel type de tuile le joueur a cliqué */
							const std::array<int, 12> myCommand = statelay.getCommandTab();
							cout<<myCommand[idCommandClicked]<<endl;

							/* On analyse la lise d'action pré-existante */
							std::array<int, 6> mySlot = statelay.getSlotTab();

							/* On cherche la dernière case vide (=0) pour ajouter l'action cliquée */
							for (int i = 0 ; i < 6 ; i++) {
								if(mySlot[i] == 0){
									mySlot[i] = myCommand[idCommandClicked];
									statelay.setSlotTab(mySlot);
									/* Quitte la boucle après un ajout (peut faire plus propre) */
									i = 6; 
								}
							}

							//statelay.setCommandTab({1, 1, 1, 1, 1, 1, 5, 14, 14, 1, 14, 14});
							
							statelay.refreshCommand();
							statelay.refreshSlot();
						}
					}
				}
			}
			window.clear();
			statelay.draw(state, window);
			window.display();
			
			
		}	

		return 0;


	} else {
		cout << "Fonction doesn't exist" << endl;
	}
	return 0;
}
