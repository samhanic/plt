#include "../render.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;
using namespace render;
#define esp_tile 0
#define larg_tile 64

bool Display::loadMap(state::State& stateLayer, sf::Texture& textureTileSet, sf::Vector2u tileSize) {
        //cout<< "Affichage tuile"<<endl;
        // on charge la texture du tileset
        // if (!m_tileset.loadFromFile(tileset))
        //     return false;
        m_tileset = textureTileSet; 
        unsigned int width = stateLayer.getWidthMap("../res/map.txt");// stateLayer.getWidthMap();
        unsigned int height = stateLayer.getHeightMap("../res/map.txt");
        // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // on remplit le tableau de vertex, avec un quad par tuile
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                
                // on récupère le numéro de tuile courant
                int tileNumber = stateLayer.getMap()[i][j]->getTileCode();
                //int tileNumber = tiles[i + j * width];

                // on en déduit sa position dans la texture du tileset
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // on définit ses quatre coins
               /* quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // on définit ses quatre coordonnées de texture
                quad[0].texCoords = sf::Vector2f(tu * esp_tile, tv * esp_tile);
                quad[1].texCoords = sf::Vector2f(tu * esp_tile +larg_tile, tv * esp_tile);
                quad[2].texCoords = sf::Vector2f(tu * esp_tile + larg_tile, tv * esp_tile + larg_tile);
                quad[3].texCoords = sf::Vector2f(tu * esp_tile, tv * esp_tile + larg_tile); */
                
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