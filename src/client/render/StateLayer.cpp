#include "../render.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace render;
using namespace state;

StateLayer::StateLayer(sf::RenderWindow& window):window(window){

}
StateLayer::StateLayer (state::State& etat, sf::RenderWindow& window):window(window){
    
}

void StateLayer::initMap (){//state::State& state){
    TileMap surfaceMap;
    //surfaceMap.load(state, tilesets[0]->getTexture, sf::Vector2u(tilesets[0]->getCellWidth(),tilesets[0]->getCellHeight()),state.getMap()[0].size());
    //surfaceMap.load(chemin,  sf::Vector2u(tilesets[0]->getCellWidth(),tilesets[0]->getCellHeight()), tilesets[0]->getTexture,state.getMap()[0].size(),state.getMap()[1].size());
    std::string map_txt = "../res/map.txt";
	MapFactory tabMapFactory = MapFactory();
	State state;
    state.initMap(map_txt, tabMapFactory);
    		// create the window
		sf::RenderWindow window(sf::VideoMode(640, 640), "RobotIS");

        int largeur =10;
        int longueur =10;
        std::ifstream fichier(map_txt, ios::in);    
        std::string contenu, ligne, code_tuile;
        
        int map_tuiles_code[largeur*longueur];
        
        // Lecture Fichier
        if (fichier){
            while (getline(fichier,ligne)){
                ligne = ligne + ",";
                contenu = contenu + ligne;
            }
            fichier.close();
            cout << contenu << endl;
        }
        else {
            cout << "le frichier ne peut être lu" << endl;
        }

        // Conversion des codes des tuiles en int
        std::stringstream contenuStream(contenu);
        int i = 0;
        
        int level[100];
        while(std::getline(contenuStream, code_tuile, ',')){
            level[i] = std::stoi(code_tuile);
            i++;
        }

		// define the level with an array of tile indices
		//const int level[]=map_tuiles_code[];

		// create the tilemap from the level definition
		TileMap map;
		if (!map.load("../res/map.png", sf::Vector2u(64, 64), level, 10, 10))
			cout<<"Erreur de chargement"<<endl;

		// run the main loop
		while (window.isOpen())
		{
			// handle events
			sf::Event event;
			while (window.pollEvent(event))
			{
				if(event.type == sf::Event::Closed)
					window.close();
			}

			// draw the map
			window.clear();
			window.draw(map);
			window.display();
		}
}