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
#include <array> 

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
    std::unique_ptr<TileSet> ptrSlotTileSet(new TileSet(COMMAND_TILESET));
    tilesets.push_back(std::move(ptrSlotTileSet));
}

void StateLayer::initSurface (state::State& stateLayer){
    Display surfaceMap;
    Display surfacePlayers;
    Display surfaceCommand;
    Display surfaceSlot;

    int inTiles[] = {8, 1, 9, 0, 5, 7, 6, 0, 0, 2, 0, 0};
    int inSlot[] = {0, 0, 0, 0, 0, 0};
    
    for (int i = 0 ; i < 12 ; i++) {
        commandTab[i] = inTiles[i];
    }
    for (int i = 0 ; i < 6 ; i++) {
        slotTab[i] = inSlot[i];
    }


    surfaceMap.loadMap(stateLayer, tilesets[0]->getTexture(), sf::Vector2u(tilesets[0]->getCellWidth(), tilesets[0]->getCellHeight()));
    surfacePlayers.loadPlayers(stateLayer, tilesets[1]->getTexture(), sf::Vector2u(tilesets[1]->getCellWidth(), tilesets[1]->getCellHeight()));
    surfaceCommand.loadCommand(tilesets[2]->getTexture(), sf::Vector2u(tilesets[2]->getCellWidth(), tilesets[2]->getCellHeight()), inTiles);
    surfaceSlot.loadSlot(tilesets[2]->getTexture(), sf::Vector2u(tilesets[2]->getCellWidth(), tilesets[2]->getCellHeight()), inSlot);


    std::unique_ptr<Display> ptrMapDisplay (new Display(surfaceMap));
    std::unique_ptr<Display> ptrPlayersDisplay (new Display(surfacePlayers));
    std::unique_ptr<Display> ptrCommandDisplay (new Display(surfaceCommand));
    std::unique_ptr<Display> ptrSlotDisplay (new Display(surfaceSlot));

    /* On nettoie/supprime les surfaces avant d'afficher les nouvelles */
    if (surfaces.size()!=0){
        while (surfaces.size()!=0){
            surfaces.pop_back();
        }
    }

    surfaces.push_back(move(ptrMapDisplay));
    surfaces.push_back(move(ptrPlayersDisplay));
    surfaces.push_back(move(ptrCommandDisplay));
    surfaces.push_back(move(ptrSlotDisplay));
}

void StateLayer::refreshCommand () {
    Display surfaceCommand;

    int inTiles[12];
    for (int i = 0 ; i < 12 ; i++) {
        inTiles[i] = commandTab[i];
    }
   
    surfaceCommand.loadCommand(tilesets[2]->getTexture(), sf::Vector2u(tilesets[2]->getCellWidth(), tilesets[2]->getCellHeight()), inTiles);
    
    std::unique_ptr<Display> ptrCommandDisplay (new Display(surfaceCommand));

    /* Attention ! il faut appeler l'initialisation de la map avant refreshCommand sinon "surfaces" n'existe pas"*/
    surfaces.at(2) = move(ptrCommandDisplay);
}

void StateLayer::refreshSlot () {
    Display surfaceSlot;

    int inSlots[6];
    for (int i = 0 ; i < 6 ; i++) {
        inSlots[i] = slotTab[i];
    }
   
    surfaceSlot.loadSlot(tilesets[2]->getTexture(), sf::Vector2u(tilesets[2]->getCellWidth(), tilesets[2]->getCellHeight()), inSlots);
    
    std::unique_ptr<Display> ptrSlotDisplay (new Display(surfaceSlot));

    /* Attention ! il faut appeler l'initialisation de la map avant refreshCommand sinon "surfaces" n'existe pas"*/
    surfaces.at(3) = move(ptrSlotDisplay);
}

void StateLayer::setCommandTab(const std::array<int,12>& commandTab) {
    this->commandTab = commandTab;
}

const std::array<int,12>& StateLayer::getCommandTab() const {
     return commandTab;
}

void StateLayer::setSlotTab(const std::array<int,6>& slotTab) {
    this->slotTab = slotTab;
}

const std::array<int,6>& StateLayer::getSlotTab() const {
     return slotTab;
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
    window.draw(*surfaces[3]);
    writeStatistics(stateLayer, window);
    window.display();
}
