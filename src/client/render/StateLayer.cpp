#include "../render.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <algorithm>
#include <string> 
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace render;
using namespace state;

StateLayer::StateLayer (state::State& myState, sf::RenderWindow& window):window(window){
    std::unique_ptr<TileSet> ptrMapTileSet(new TileSet(MAP_TILESET));
    tilesets.push_back(std::move(ptrMapTileSet));
    std::unique_ptr<TileSet> ptrPawnTileSet(new TileSet(PAWN_TILESET));
    tilesets.push_back(std::move(ptrPawnTileSet));
    std::unique_ptr<TileSet> ptrCommandTileSet(new TileSet(COMMAND_TILESET));
    tilesets.push_back(std::move(ptrCommandTileSet));
}

void StateLayer::initSurface (state::State& stateLayer){
    Display surfaceMap;
    Display surfacePlayers;
    Display surfaceCommand;

    surfaceMap.loadMap(stateLayer, tilesets[0]->getTexture(), sf::Vector2u(tilesets[0]->getCellWidth(), tilesets[0]->getCellHeight()));
    surfacePlayers.loadPlayers(stateLayer, tilesets[1]->getTexture(), sf::Vector2u(tilesets[1]->getCellWidth(), tilesets[1]->getCellHeight()));
    surfaceCommand.loadCommand(stateLayer, tilesets[2]->getTexture(), sf::Vector2u(tilesets[2]->getCellWidth(), tilesets[2]->getCellHeight()));

    std::unique_ptr<Display> ptrMapDisplay (new Display(surfaceMap));
    std::unique_ptr<Display> ptrPlayersDisplay (new Display(surfacePlayers));
    std::unique_ptr<Display> ptrCommandDisplay (new Display(surfaceCommand));

    if (surfaces.size()!=0){
        while (surfaces.size()!=0){
            surfaces.pop_back();
        }
    }

    surfaces.push_back(move(ptrMapDisplay));
    surfaces.push_back(move(ptrPlayersDisplay));
    surfaces.push_back(move(ptrCommandDisplay));
}

void StateLayer::writeStatistics (state::State& stateLayer, sf::RenderWindow& window) {
    
    sf::Font font;
	if(!font.loadFromFile("../res/Roboto/Roboto-Regular.ttf")) {
        cerr << "Fichier de police introuvable" <<  endl;
    }
	for (unsigned int i = 0 ; i < stateLayer.players.size() ; i++ ) {  
        // Convert to string
        int idColor = stateLayer.getPlayers()[i]->getTileCode();
        std::string robotColor = "null";
        if (idColor == 0) {
            robotColor = "(pink)";
        } else if (idColor == 1) {
             robotColor = "(blue)";
        } else if (idColor == 2) {
             robotColor = "(yellow)";
        } else if (idColor == 3) {
             robotColor = "(orange)";
        } else if (idColor == 4) {
             robotColor = "(red)";
        }
        std::string robotNumber = std::to_string(i+1);
        std::string robotLifes = std::to_string(stateLayer.getPlayers()[i]->getLifeNumber());     
        std::string robotHP = std::to_string(stateLayer.getPlayers()[i]->getLifePoints()); 

        sf::Text text("Robot" + robotNumber + " " + robotColor + " | L : " + robotLifes + "/3 | HP : " + robotHP + "/5", font);
        text.setCharacterSize(13);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::White);
        text.setPosition(650, 320 + (20 * i));
        window.draw(text);
    }
}

void StateLayer::draw (state::State& stateLayer, sf::RenderWindow& window){
    window.clear();
    window.draw(*surfaces[0]);
    window.draw(*surfaces[1]);
    window.draw(*surfaces[2]);
    writeStatistics(stateLayer, window);
    window.display();
}
