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
    cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!" <<endl;
}
StateLayer::StateLayer (state::State& etat, sf::RenderWindow& window):window(window){
    std::unique_ptr<TileSet> ptr_mapTileSet(new TileSet(MAP_TILESET));
    tilesets.push_back(std::move(ptr_mapTileSet));
}

void StateLayer::initSurface (state::State& etatLayer){
    TileMap surfaceMap;
    // cout<<"calcul de la profondeur"<<endl;
    // int width = tilesets[0]->getCellWidth();
    // cout<<width<<endl;
    //sf::Vector2u(tilesets[0]->getCellWidth(), tilesets[0]->getCellHeight());
    // cout<<"Non vraiement entree"<<endl;
    surfaceMap.load(etatLayer, tilesets[0]->getTexture(), sf::Vector2u(tilesets[0]->getCellWidth(), tilesets[0]->getCellHeight()));

    std::unique_ptr<TileMap> ptr_tileMap (new TileMap(surfaceMap));

    if (surfaces.size()!=0){
        while (surfaces.size()!=0){
            surfaces.pop_back();
        }
    }

    surfaces.push_back(move(ptr_tileMap));

    //surfaceMap.load(state, tilesets[0]->getTexture, sf::Vector2u(tilesets[0]->getCellWidth(),tilesets[0]->getCellHeight()),state.getMap()[0].size());
    //surfaceMap.load(chemin,  sf::Vector2u(tilesets[0]->getCellWidth(),tilesets[0]->getCellHeight()), tilesets[0]->getTexture,state.getMap()[0].size(),state.getMap()[1].size());
    // std::string map_txt = "../res/map.txt";
	// MapFactory tabMapFactory = MapFactory();
	// State state;
    // state.initMap(map_txt, tabMapFactory);
    // 	// create the window
	// 	sf::RenderWindow window(sf::VideoMode(640, 640), "RobotIS");

    //     std::ifstream fichier(map_txt, ios::in);    
    //     std::string contenu, ligne, code_tuile;
                
    //     // Lecture Fichier
    //     if (fichier){
    //         while (getline(fichier,ligne)){
    //             ligne = ligne + ",";
    //             contenu = contenu + ligne;
    //         }
    //         fichier.close();
    //         cout << contenu << endl;
    //     }
    //     else {
    //         cout << "le frichier ne peut être lu" << endl;
    //     }

    //     // Conversion des codes des tuiles en int
    //     std::stringstream contenuStream(contenu);
    //     int i = 0;
        
    //     int level[100];
    //     while(std::getline(contenuStream, code_tuile, ',')){
    //         level[i] = std::stoi(code_tuile);
    //         i++;
    //     }

	// 	// define the level with an array of tile indices
	// 	//const int level[]=map_tuiles_code[];

	// 	// create the tilemap from the level definition
	// 	TileMap map;
	// 	if (!map.load("../res/map.png", sf::Vector2u(64, 64), level, 10, 10))
	// 		cout<<"Erreur de chargement"<<endl;

	// 	// run the main loop
	// 	while (window.isOpen())
	// 	{
	// 		// handle events
	// 		sf::Event event;
	// 		while (window.pollEvent(event))
	// 		{
	// 			if(event.type == sf::Event::Closed)
	// 				window.close();
	// 		}

	// 		// draw the map
	// 		window.clear();
	// 		window.draw(map);
	// 		window.display();
	// 	}
}

void StateLayer::draw (sf::RenderWindow& window){
    window.clear();
    window.draw(*surfaces[0]);
    window.display();
}