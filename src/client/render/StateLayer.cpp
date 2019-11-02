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

    surfaceMap.loadMap(stateLayer, tilesets[0]->getTexture(), sf::Vector2u(tilesets[0]->getCellWidth(), tilesets[0]->getCellHeight()));
    surfacePlayers.loadPlayers(stateLayer, tilesets[1]->getTexture(), sf::Vector2u(tilesets[1]->getCellWidth(), tilesets[1]->getCellHeight()));

    std::unique_ptr<Display> ptrMapDisplay (new Display(surfaceMap));
    std::unique_ptr<Display> ptrPlayersDisplay (new Display(surfacePlayers));

    if (surfaces.size()!=0){
        while (surfaces.size()!=0){
            surfaces.pop_back();
        }
    }

    surfaces.push_back(move(ptrMapDisplay));
    surfaces.push_back(move(ptrPlayersDisplay));
}

void StateLayer::draw (sf::RenderWindow& window){
    window.clear();
    window.draw(*surfaces[0]);
    window.draw(*surfaces[1]);
    window.display();
}