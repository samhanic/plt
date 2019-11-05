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
						int slotPosition = 0; // Position du dernier slot vide
						/* On recupère la position dans le slot */
						std::array<int, 6> mySlot = statelay.getSlotTab();

						
						for (int i = 0 ; i < 6 ; i++) {
							if (mySlot[i] == 0) {
								slotPosition = i;
								break;
							}
						}
						if (mySlot[5] != 0) {
							slotPosition = 6;
							statelay.setCommandTab({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
						}
						cout<<"Slot position deb : "<<slotPosition<<endl;
						
						/* Detection zones de clique (a remplacer par génération d'un tableau) */
						if ((event.mouseButton.x > 690) && (event.mouseButton.x < 730)
						&& (event.mouseButton.y > 100) && (event.mouseButton.y < 140)) {
							idCommandClicked = 0;
						} else if ((event.mouseButton.x > 730) && (event.mouseButton.x < 770)
						&& (event.mouseButton.y > 100) && (event.mouseButton.y < 140)) {
							idCommandClicked = 1;
						} else if ((event.mouseButton.x > 770) && (event.mouseButton.x < 810)
						&& (event.mouseButton.y > 100) && (event.mouseButton.y < 140)) {
							idCommandClicked = 2;
						} else if ((event.mouseButton.x > 810) && (event.mouseButton.x < 850)
						&& (event.mouseButton.y > 100) && (event.mouseButton.y < 140)) {
							idCommandClicked = 3;
						} else if ((event.mouseButton.x > 690) && (event.mouseButton.x < 730)
						&& (event.mouseButton.y > 140) && (event.mouseButton.y < 180)) {
							idCommandClicked = 4;
						} else if ((event.mouseButton.x > 730) && (event.mouseButton.x < 770)
						&& (event.mouseButton.y > 140) && (event.mouseButton.y < 180)) {
							idCommandClicked = 5;
						} else if ((event.mouseButton.x > 770) && (event.mouseButton.x < 810)
						&& (event.mouseButton.y > 140) && (event.mouseButton.y < 180)) {
							idCommandClicked = 6;
						} else if ((event.mouseButton.x > 810) && (event.mouseButton.x < 850)
						&& (event.mouseButton.y > 140) && (event.mouseButton.y < 180)) {
							idCommandClicked = 7;
						} else if ((event.mouseButton.x > 690) && (event.mouseButton.x < 730)
						&& (event.mouseButton.y > 180) && (event.mouseButton.y < 220)) {
							idCommandClicked = 8;
						} else if ((event.mouseButton.x > 730) && (event.mouseButton.x < 770)
						&& (event.mouseButton.y > 180) && (event.mouseButton.y < 220)) {
							idCommandClicked = 9;
						} else if ((event.mouseButton.x > 770) && (event.mouseButton.x < 810)
						&& (event.mouseButton.y > 180) && (event.mouseButton.y < 220)) {
							idCommandClicked = 10;
						} else if ((event.mouseButton.x > 810) && (event.mouseButton.x < 850)
						&& (event.mouseButton.y > 180) && (event.mouseButton.y < 220)) {
							idCommandClicked = 11;
						}
						/* Détection d'un clique sur la slot barre */
						else if ((event.mouseButton.x > 645) && (event.mouseButton.x < 685)
						&& (event.mouseButton.y > 30) && (event.mouseButton.y < 70)) {
							idCommandClicked = 20;
						} else if ((event.mouseButton.x > 685) && (event.mouseButton.x < 725)
						&& (event.mouseButton.y > 30) && (event.mouseButton.y < 70)) {
							idCommandClicked = 21;
						} else if ((event.mouseButton.x > 725) && (event.mouseButton.x < 765)
						&& (event.mouseButton.y > 30) && (event.mouseButton.y < 70)) {
							idCommandClicked = 22;
						} else if ((event.mouseButton.x > 765) && (event.mouseButton.x < 805)
						&& (event.mouseButton.y > 30) && (event.mouseButton.y < 70)) {
							idCommandClicked = 23;
						} else if ((event.mouseButton.x > 805) && (event.mouseButton.x < 845)
						&& (event.mouseButton.y > 30) && (event.mouseButton.y < 70)) {
							idCommandClicked = 24;
						} else if ((event.mouseButton.x > 845) && (event.mouseButton.x < 885)
						&& (event.mouseButton.y > 30) && (event.mouseButton.y < 70)) {
							idCommandClicked = 25;
						}

						/* La zone slot bar a été cliquée pour nettoyage des actions */
						if (idCommandClicked >= 20 && idCommandClicked <= 25) {
							slotPosition = idCommandClicked - 20;
							for (int i = 5 ; i >= 0 ; i--) {
								/* On supprime les actions derrière l'action cliquée */
								if (i >= slotPosition) {
									mySlot[i] = 0;
								}
							}					
							statelay.setSlotTab(mySlot);
						}

						/* Une zone de commande a été cliquée */
						if (idCommandClicked != -1 && idCommandClicked <= 11) {
							/* On regarde sur quel type de tuile le joueur a cliqué */
							std::array<int, 12> myCommand = statelay.getCommandTab();
							if (slotPosition <= 5 ) {
								slotPosition ++;
							}

							/* On cherche la dernière case vide (=0) pour ajouter l'action cliquée */
							for (int i = 0 ; i < 6 ; i++) {
								if(mySlot[i] == 0){
									mySlot[i] = myCommand[idCommandClicked];
									statelay.setSlotTab(mySlot);
									statelay.refreshSlot();
									/* Quitte la boucle après un ajout */
									break; 
								}
								/* Affichage après supression de commande en fonction de la commande précédente */
								if (slotPosition > 0) {
									/* cas booster avant dernier */
									if (mySlot[slotPosition] == 5 && slotPosition == 5) {
										statelay.setCommandTab({0, 1, 0, 0, 3, 0, 4, 0, 0, 2, 0, 0});
									} else if (mySlot[slotPosition] == 5) {
										statelay.setCommandTab({0, 1, 0, 0, 3, 7, 4, 0, 0, 2, 0, 0});
									} else if (mySlot[slotPosition] != 5) {
										statelay.setCommandTab({8, 1, 9, 0, 5, 7, 6, 0, 0, 2, 0, 0});
									}
								} else {
									statelay.setCommandTab({8, 1, 9, 0, 5, 7, 6, 0, 0, 2, 0, 0});
								}


							}
							/* Cas particulier du booster */
							if (idCommandClicked == 5 ) {
								/* Si avant derniere action on ne peut plus boost */
								if (slotPosition <= 5 && mySlot[slotPosition ] != 5 ) {
									statelay.setCommandTab({0, 1, 0, 0, 3, 7, 4, 0, 0, 2, 0, 0});
								} else {
									statelay.setCommandTab({8, 1, 9, 0, 5, 0, 6, 0, 0, 2, 0, 0});
								}
							} else {
								statelay.setCommandTab({8, 1, 9, 0, 5, 7, 6, 0, 0, 2, 0, 0});
							}						
						}
						if (mySlot[5] != 0) {
							statelay.setButtonReadyToClick(1);						
						} else {
							statelay.setButtonReadyToClick(0);
						}
						
						
						cout<<"Slot position fin : "<<slotPosition<<endl;
						statelay.refreshCommand();
						statelay.refreshSlot();
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
