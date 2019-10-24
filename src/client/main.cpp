#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>


#include "../../src/shared/state.h"
#include "../../src/client/render.h"

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
	} else if (entry == "render") {

		sf::RenderWindow window(sf::VideoMode(1, 1), "RobotIS");
		StateLayer statelayer(window);
		statelayer.initSurface();
	
	State state;
	MapFactory mapFactory;
	state.initMap("../res/map.txt", mapFactory);
		/* TESTS DE RENDU */
		
		
		// std::string chemin_fichier_map_txt = "../res/map.txt";
		// MapFactory tabMapFactory = MapFactory();
		// State state;
		

		// state.initMap(chemin_fichier_map_txt, tabMapFactory);
		//cout <<"MYX : "<<'\t'<<state.getMap()[2][1]->getPosition().getX()<<'\t'<< endl;
		// sf::RenderWindow renderWindow(sf::VideoMode(800, 550), "RobotIS");
		// //sf::Texture texture;
		// //texture.loadFromFile("../res/map.png");
		// //sf::Sprite sprite(texture);
		
		// StateLayer stateLayer(state, renderWindow);
		// stateLayer.initSurfaces(state);
		// stateLayer.draw(renderWindow);
				
			
		// while (renderWindow.isOpen()){
		// 	sf::Event event;
		// 	while (renderWindow.pollEvent(event)){
		// 		if (event.type == sf::Event::EventType::Closed) {
		// 			renderWindow.close();
		// 		}
		// 	}
		// 	renderWindow.clear();
		// 	//renderWindow.draw(sprite);
		// 	renderWindow.display();
		// }
   		

		// create the window
		// sf::RenderWindow window(sf::VideoMode(640, 640), "RobotIS");

		// // define the level with an array of tile indices
		// const int level[] =
		// {
		// 	0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		// 	0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		// 	1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
		// 	0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
		// 	0, 1, 1, 0, 3, 3, 3, 8, 0, 0, 1, 1, 1, 2, 0, 0,
		// 	0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 18, 1, 1, 1, 2, 0,
		// 	2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		// 	0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
		// };

		// // create the tilemap from the level definition
		// TileMap map;
		// if (!map.load("../res/map.png", sf::Vector2u(64, 64), level, 10, 10))
		// 	return -1;

		// // run the main loop
		// while (window.isOpen())
		// {
		// 	// handle events
		// 	sf::Event event;
		// 	while (window.pollEvent(event))
		// 	{
		// 		if(event.type == sf::Event::Closed)
		// 			window.close();
		// 	}

		// 	// draw the map
		// 	window.clear();
		// 	window.draw(map);
		// 	window.display();
		// }

		return 0;


	} else {
		cout << "Fonction doesn't exist" << endl;
	}
	return 0;
}
