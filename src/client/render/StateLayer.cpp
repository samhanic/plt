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
    std::unique_ptr<TileSet> ptr_mapTileSet(new TileSet(MAP_TILESET));
    tilesets.push_back(std::move(ptr_mapTileSet));
}

void StateLayer::initSurface (state::State& stateLayer){
    Display surfaceMap;

    surfaceMap.loadMap(stateLayer, tilesets[0]->getTexture(), sf::Vector2u(tilesets[0]->getCellWidth(), tilesets[0]->getCellHeight()));

    std::unique_ptr<Display> ptr_display (new Display(surfaceMap));

    if (surfaces.size()!=0){
        while (surfaces.size()!=0){
            surfaces.pop_back();
        }
    }

    surfaces.push_back(move(ptr_display));
}

void StateLayer::draw (sf::RenderWindow& window){
    window.clear();
    window.draw(*surfaces[0]);
    window.display();
}