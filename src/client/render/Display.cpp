#include "../render.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;
using namespace render;
#define esp_tile 0
#define larg_tile 64

bool Display::loadMap(state::State& stateLayer, sf::Texture& textureTileSet, sf::Vector2u tileSize) {

    m_tileset = textureTileSet; 
    unsigned int width = stateLayer.getWidthMap("../res/map.txt");
    unsigned int height = stateLayer.getHeightMap("../res/map.txt");
    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
             
            // on récupère le numéro de tuile courant
            int tileNumber = stateLayer.getMap()[i][j]->getTileCode();
            //int tileNumber = tiles[i + j * width];

            // on en déduit sa position dans la texture du tileset
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // on définit ses quatre coins                
            quad[0].position = sf::Vector2f(stateLayer.getMap()[j][i]->getPosition().getX() * tileSize.x, stateLayer.getMap()[j][i]->getPosition().getY() * tileSize.y);
    		quad[1].position = sf::Vector2f((stateLayer.getMap()[j][i]->getPosition().getX()+ 1) * tileSize.x, stateLayer.getMap()[j][i]->getPosition().getY() * tileSize.y);
			quad[2].position = sf::Vector2f((stateLayer.getMap()[j][i]->getPosition().getX() + 1) * tileSize.x, (stateLayer.getMap()[j][i]->getPosition().getY() + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(stateLayer.getMap()[j][i]->getPosition().getX() * tileSize.x, (stateLayer.getMap()[j][i]->getPosition().getY() + 1) * tileSize.y);
				
            // on définit ses quatre coordonnées de texture
			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
    return true;
}

bool Display::loadCommand(state::State& stateLayer, sf::Texture& textureTileSet, sf::Vector2u tileSize) {

    m_tileset = textureTileSet; 
    unsigned int width = 4;
    unsigned int height = 3;

    unsigned int widthMap = stateLayer.getWidthMap("../res/map.txt");
    unsigned int offsetCommandX = 64 * widthMap + 50;
    unsigned int offsetCommandY = 100;
    

    const int initTiles[] =
    {
        7, 0, 8, 14,
        4, 6, 5, 14,
        14, 1, 14, 14,
    };

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {

           int tileNumber = initTiles[i + j * width];

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x + offsetCommandX, j * tileSize.y + offsetCommandY);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x + offsetCommandX, j * tileSize.y + offsetCommandY);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x + offsetCommandX, (j + 1) * tileSize.y + offsetCommandY);
            quad[3].position = sf::Vector2f(i * tileSize.x + offsetCommandX, (j + 1) * tileSize.y + offsetCommandY);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
    return true;
}

bool Display::loadSlot(state::State& stateLayer, sf::Texture& textureTileSet, sf::Vector2u tileSize) {

    m_tileset = textureTileSet; 
    unsigned int width = 6;
    unsigned int height = 1;

    unsigned int widthMap = stateLayer.getWidthMap("../res/map.txt");
    unsigned int offsetCommandX = 64 * widthMap + 5;
    unsigned int offsetCommandY = 30;
    

    const int initTiles[] =
    {
        14, 14, 14, 14, 14, 14,
    };

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {

           int tileNumber = initTiles[i + j * width];

            // find its position in the tileset texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x + offsetCommandX, j * tileSize.y + offsetCommandY);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x + offsetCommandX, j * tileSize.y + offsetCommandY);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x + offsetCommandX, (j + 1) * tileSize.y + offsetCommandY);
            quad[3].position = sf::Vector2f(i * tileSize.x + offsetCommandX, (j + 1) * tileSize.y + offsetCommandY);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
    return true;
    
}

bool Display::loadPlayers (state::State& stateLayer, sf::Texture& textureTileSet, sf::Vector2u tileSize) {

    m_tileset = textureTileSet; 
	
    unsigned int width = stateLayer.getWidthMap("../res/map.txt");
    unsigned int height = stateLayer.getHeightMap("../res/map.txt");

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    //cout << stateLayer.getPlayers()[0]->getTileCode() << endl;
    
    for (unsigned int i = 0; i < stateLayer.getPlayers().size(); ++i){
        //On met a jour les tuiles des personnages en fonction de leur statut
        
        // A FAIRE
        //updateTilesPersonnages(etatLayer);
        // on récupère le numéro de tuile courant
		int tileNumber=stateLayer.getPlayers()[i]->getTileCode();	
        // on en déduit sa position dans la texture du tileset
        int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
        int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

        // on récupère un pointeur vers le quad à définir dans le tableau de vertex
        sf::Vertex* quad = &m_vertices[i * 4];
				
		// on définit ses quatre coins                
        quad[0].position = sf::Vector2f(stateLayer.getPlayers()[i]->getPosition().getX() * tileSize.x, stateLayer.getPlayers()[i]->getPosition().getY() * tileSize.y);
    	quad[1].position = sf::Vector2f((stateLayer.getPlayers()[i]->getPosition().getX()+ 1) * tileSize.x, stateLayer.getPlayers()[i]->getPosition().getY() * tileSize.y);
		quad[2].position = sf::Vector2f((stateLayer.getPlayers()[i]->getPosition().getX() + 1) * tileSize.x, (stateLayer.getPlayers()[i]->getPosition().getY() + 1) * tileSize.y);
		quad[3].position = sf::Vector2f(stateLayer.getPlayers()[i]->getPosition().getX() * tileSize.x, (stateLayer.getPlayers()[i]->getPosition().getY() + 1) * tileSize.y);
				
        // on définit ses quatre coordonnées de texture
		quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
		quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
		quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
		quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
	}
   
	return true;
}

void  Display::draw (sf::RenderTarget& target, sf::RenderStates states) const {
        // on applique la transformation
        states.transform *= getTransform();

        // on applique la texture du tileset
        states.texture = &m_tileset;

        // et on dessine enfin le tableau de vertex
        target.draw(m_vertices, states);
}
