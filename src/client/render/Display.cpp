#include "../render.h"
#include "../../shared/state.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;
using namespace render;
using namespace state;
#define esp_tile 0
#define larg_tile 64

bool Display::loadMap(state::State& stateLayer, sf::Texture& textureTileSet, sf::Vector2u tileSize) {

    m_tileset = textureTileSet; 
    unsigned int width = stateLayer.getMapWidth();
    unsigned int height = stateLayer.getMapHeight();
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

bool Display::loadEffects (state::State& stateLayer, sf::Texture& textureTileSet, sf::Vector2u tileSize) {
    m_tileset = textureTileSet; 
    unsigned int width = stateLayer.getMapWidth();
    unsigned int height = stateLayer.getMapHeight();
    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);
    
    int tileNumber;
    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {
            tileNumber = 34;
            // on récupère le numéro de tuile courant
           
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

bool Display::loadCommand(sf::Texture& textureTileSet, sf::Vector2u tileSize, int tabCommand[]) {

    m_tileset = textureTileSet; 
    unsigned int width = 4;
    unsigned int height = 3;

    unsigned int widthMap = 10; // A automatiser
    unsigned int offsetCommandX = 64 * widthMap + 50;
    unsigned int offsetCommandY = 100;
    

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {

           int tileNumber = tabCommand[i + j * width];

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

bool Display::loadSlot (sf::Texture& textureTileSet, sf::Vector2u tileSize, int tabSlot[]) {
    m_tileset = textureTileSet; 
    unsigned int width = 6;
    unsigned int height = 1;

    unsigned int widthMap = 10; // A généraliser en fct de la map chargée
    unsigned int offsetCommandX = 64 * widthMap + 5;
    unsigned int offsetCommandY = 30;
    

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {

           int tileNumber = tabSlot[i + j * width];

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
	
    unsigned int width = stateLayer.getMapWidth();
    unsigned int height = stateLayer.getMapHeight();

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width * height * 4);

    //cout << stateLayer.getPlayers()[0]->getTileCode() << endl;
    
    for (unsigned int i = 0; i < stateLayer.getPlayers().size(); ++i){
        int tileNumber = 0;
        // Add orientation render
        if (stateLayer.getPlayers()[i]->getOrientation()== NORTH) {
           tileNumber=stateLayer.getPlayers()[i]->getTileCode();
           cout<<"vers nord"<<endl;
        } else if (stateLayer.getPlayers()[i]->getOrientation()== EAST) {
            tileNumber=stateLayer.getPlayers()[i]->getTileCode()+5;
            cout<<"vers est"<<endl;
        } else if (stateLayer.getPlayers()[i]->getOrientation()== WEST) {
            tileNumber=stateLayer.getPlayers()[i]->getTileCode()+10;
            cout<<"vers ouest"<<endl;
        } else if (stateLayer.getPlayers()[i]->getOrientation()== SOUTH) {
            tileNumber=stateLayer.getPlayers()[i]->getTileCode()+15;
            cout<<"vers sud"<<endl;
        }


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
