#include "Surface.h"
#include "../render.h"
//#include "../../shared/state/TypeId.h"
#include "../../shared/state.h"

using namespace render;
using namespace state;

#define tile_gap 80

bool Surface::loadGrille(state::State& etatLayer, sf::Texture& textureTileset, sf::Vector2u tileSize, unsigned int width, unsigned int  height){
    			
	texture = textureTileset;
		
    //On redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	quads.setPrimitiveType(sf::Quads);
    quads.resize(width * height * 4);

    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; i++){
        for (unsigned int j = 0; j < height; j++){
            // on récupère le numéro de tuile courant
            TypeId tileNumber = etatLayer.getMap()[i][j]->getTypeId();
            //etatLayer est un &state::Etat
            //etatLayer.getMap() est un vect de vect de std::unique_ptr<terrain>&
            //etatLayer.getMap()[i][j] est un state::Maptile&

            //on récupère la position dans le tileset
            int posu = tileNumber %(texture.getSize().x/tileSize.x);
            int posv = tileNumber / (texture.getSize().x/tileSize.x);

            //on récupère un pointeur vers le quad à définir dans le tableau de vertex
            sf::Vertex* quad = &quads[(i + j * width) * 4];
            // on définit ses quatre coins
			quad[0].position = sf::Vector2f(etatLayer.getMap()[j][i]->getPosition().getX() * tileSize.x, etatLayer.getMap()[j][i]->getPosition().getY() * tileSize.y);
			quad[1].position = sf::Vector2f((etatLayer.getMap()[j][i]->getPosition().getX()+ 1) * tileSize.x, etatLayer.getMap()[j][i]->getPosition().getY() * tileSize.y);
			quad[2].position = sf::Vector2f((etatLayer.getMap()[j][i]->getPosition().getX() + 1) * tileSize.x, (etatLayer.getMap()[j][i]->getPosition().getY() + 1) * tileSize.y);
			quad[3].position = sf::Vector2f(etatLayer.getMap()[j][i]->getPosition().getX() * tileSize.x, (etatLayer.getMap()[j][i]->getPosition().getY() + 1) * tileSize.y);

            // on définit ses quatre coordonnées de texture
			quad[0].texCoords = sf::Vector2f(posu * tileSize.x, posv * tileSize.y);
			quad[1].texCoords = sf::Vector2f((posu + 1) * tileSize.x, posv * tileSize.y);
			quad[2].texCoords = sf::Vector2f((posu + 1) * tileSize.x, (posv + 1) * tileSize.y);
			quad[3].texCoords = sf::Vector2f(posu * tileSize.x, (posv + 1) * tileSize.y);					
        }
	}
	return true;	
}


bool Surface::loadPersonnage(state::State& etatLayer, sf::Texture& textureTileset, sf::Vector2u tileSize, unsigned int width, unsigned int height){
    this->texture = textureTileset;

    // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
	quads.setPrimitiveType(sf::Quads);
    quads.resize(width * height * 4);
    // on remplit le tableau de vertex, avec un quad par tuile
    for (unsigned int i = 0; i < width; ++i){
    	//On met a jour les tuiles des personnages en fonction de leur statut
    	updateTilesPersonnages(etatLayer);
       	// on récupère le numéro de tuile courant
		TypeId tileNumber=etatLayer.getPlayers()[i]->getTypeId();
	
        // on en déduit sa position dans la texture du tileset
        int tu = tileNumber % (texture.getSize().x / tileSize.x);
        int tv = tileNumber / (texture.getSize().x / tileSize.x);
        // on récupère un pointeur vers le quad à définir dans le tableau de vertex
        sf::Vertex* quad = &quads[i * 4];
			
		// on définit ses quatre coins
		quad[0].position = sf::Vector2f(etatLayer.getPlayers()[i]->getPosition().getX() * tileSize.x, etatLayer.getPlayers()[i]->getPosition().getY() * tileSize.y);
		quad[1].position = sf::Vector2f((etatLayer.getPlayers()[i]->getPosition().getX()+ 1) * tileSize.x, etatLayer.getPlayers()[i]->getPosition().getY() * tileSize.y);
		quad[2].position = sf::Vector2f((etatLayer.getPlayers()[i]->getPosition().getX() + 1) * tileSize.x, (etatLayer.getPlayers()[i]->getPosition().getY() + 1) * tileSize.y);
		quad[3].position = sf::Vector2f(etatLayer.getPlayers()[i]->getPosition().getX() * tileSize.x, (etatLayer.getPlayers()[i]->getPosition().getY() + 1) * tileSize.y);
				
        // on définit ses quatre coordonnées de texture
		quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
		quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
		quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
		quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
    }
	return true;
}

// bool Surface::loadCurseur(state::Etat& etatLayer, sf::Texture& textureTileset, sf::Vector2u tileSize, unsigned int width, unsigned int height){
    			
// 		texture = textureTileset;
		
//       	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
// 	   	quads.setPrimitiveType(sf::Quads);
//        	quads.resize(width * height * 4);
		
// 	  	// on récupère le numéro de tuile courant
// 		int tileNumber=etatLayer.getCurseur()->getCodeTuile();
		
// 	    // on en déduit sa position dans la texture du tileset
// 	    int tu = tileNumber % (texture.getSize().x / tileSize.x);
// 	    int tv = tileNumber / (texture.getSize().x / tileSize.x);

// 	    // on récupère un pointeur vers le quad à définir dans le tableau de vertex
// 	    sf::Vertex* quad = &quads[0];
		
// 		// on définit ses quatre coins
// 		quad[0].position = sf::Vector2f(etatLayer.getCurseur()->getPosition().getX() * tileSize.x, etatLayer.getCurseur()->getPosition().getY() * tileSize.y);
// 		quad[1].position = sf::Vector2f((etatLayer.getCurseur()->getPosition().getX()+ 1) * tileSize.x, etatLayer.getCurseur()->getPosition().getY() * tileSize.y);
// 		quad[2].position = sf::Vector2f((etatLayer.getCurseur()->getPosition().getX() + 1) * tileSize.x, (etatLayer.getCurseur()->getPosition().getY() + 1) * tileSize.y);
// 		quad[3].position = sf::Vector2f(etatLayer.getCurseur()->getPosition().getX() * tileSize.x, (etatLayer.getCurseur()->getPosition().getY() + 1) * tileSize.y);
		
// 		// on définit ses quatre coordonnées de texture
// 		quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
// 		quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
// 		quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
// 		quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
		

// 		return true;
// }

// bool Surface::loadInfos(state::Etat& etatLayer, sf::Texture& textureTileset, sf::Vector2u tileSize, unsigned int width, unsigned int height){

// 	texture = textureTileset;
		
//   	// on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
//    	quads.setPrimitiveType(sf::Quads);
//    	quads.resize(width * height * 4);
//     // on remplit le tableau de vertex, avec un quad par tuile
//     for (unsigned int i = 0; i < width; ++i){
//     	if(etatLayer.getPlayers()[i]->getStatut()==state::SELECTIONNE || etatLayer.getPlayers()[i]->getStatut()==state::CIBLE){
//           	// on récupère le numéro de tuile courant
// 			int tileNumber=etatLayer.getPlayers()[i]->getCodeTuile();
			
//             // on en déduit sa position dans la texture du tileset
//             int tu = tileNumber % (texture.getSize().x / tileSize.x);
//             int tv = tileNumber / (texture.getSize().x / tileSize.x);

//             // on récupère un pointeur vers le quad à définir dans le tableau de vertex
//             sf::Vertex* quad = &quads[i * 4];
			
// 			if (etatLayer.getPlayers()[i]->getCamp()==true){
// 				quad[0].position = sf::Vector2f(5+64,440);
// 				quad[1].position = sf::Vector2f(0+5,440);
// 				quad[3].position = sf::Vector2f(5+64,440+64);
// 				quad[2].position = sf::Vector2f(0+5,440+64);
// 			}
				
// 			// Personnage de l'armee rouge affiché à droite
// 			else{
// 				quad[0].position = sf::Vector2f(400-5-64,440);
// 				quad[1].position = sf::Vector2f(400-5,440);
// 				quad[2].position = sf::Vector2f(400-5,440+64);
// 				quad[3].position = sf::Vector2f(400-5-64,440+64);		
// 			}
			
// // on définit ses quatre coordonnées de texture
// 			quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
// 			quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
// 			quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
// 			quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
// 		}
// 	}

// 	return true;

// 	/*
// 	texture = textureTileset;
		
//     // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
// 	quads.setPrimitiveType(sf::Quads);
//     quads.resize(width * height * 4);
		
// 	// on récupère le numéro de tuile courant
// 	int tileNumber=8;
// 	int indicePerso=-1;
		
// 	for (size_t i = 0; i< etatLayer.getPlayers().size(); i++){
// 		if (etatLayer.getPlayers()[i]->getStatut()==state::SELECTIONNE){
// 			tileNumber = etatLayer.getPlayers()[i]->getCodeTuile();
// 			indicePerso = i;
// 			break;
// 		}
// 	}
		
// 	// on en déduit sa position dans la texture du tileset
// 	int tu = tileNumber % (texture.getSize().x / tileSize.x);
// 	int tv = tileNumber / (texture.getSize().x / tileSize.x);
// 	// on récupère un pointeur vers le quad à définir dans le tableau de vertex
// 	sf::Vertex* quad = &quads[0];
// 	if(indicePerso!=-1){
// 		// Personnage de l'armee bleue affiché à gauche
// 		if (etatLayer.getPlayers()[indicePerso]->getCamp()==true){
// 			quad[0].position = sf::Vector2f(5+64,440);
// 			quad[1].position = sf::Vector2f(0+5,440);
// 			quad[3].position = sf::Vector2f(5+64,440+64);
// 			quad[2].position = sf::Vector2f(0+5,440+64);
// 		}
			
// 		// Personnage de l'armee rouge affiché à droite
// 		else{
// 			quad[0].position = sf::Vector2f(400-5-64,440);
// 			quad[1].position = sf::Vector2f(400-5,440);
// 			quad[2].position = sf::Vector2f(400-5,440+64);
// 			quad[3].position = sf::Vector2f(400-5-64,440+64);		
// 		}
// 	}
		
// 	// on définit ses quatre coordonnées de texture
// 	quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
// 	quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
// 	quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
// 	quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
	
// 	return true;*/
// }

// void Surface::draw(sf::RenderTarget& target, sf::RenderStates states) const {
//         // on applique la transformation
//         states.transform *= getTransform();

//         // on applique la texture du tileset
//         states.texture = &texture;

//         // et on dessine enfin le tableau de vertex
//         target.draw(quads, states);
// }

// void Surface::updateTilesPersonnages(state::Etat&  etatLayer){
// 	for (unsigned int i = 0; i < etatLayer.getPlayers().size(); i++){
// 		if (etatLayer.getPlayers()[i]->getStatut() == state::DISPONIBLE){
// 			if (etatLayer.getPlayers()[i]->getCamp() == true){
// 				if (etatLayer.getPlayers()[i]->getType() == state::ARCHER){
// 					etatLayer.getPlayers()[i]->setCodeTuile(0);
// 				}
// 				else if (etatLayer.getPlayers()[i]->getType() == state::BRIGAND){
// 					etatLayer.getPlayers()[i]->setCodeTuile(1);
// 				}
// 				else if (etatLayer.getPlayers()[i]->getType() == state::GUERRIER){
// 					etatLayer.getPlayers()[i]->setCodeTuile(2);
// 				}
// 				if (etatLayer.getPlayers()[i]->getType() == state::CHEVALIER){
// 					etatLayer.getPlayers()[i]->setCodeTuile(3);
// 				}
// 			}
// 			else if (etatLayer.getPlayers()[i]->getCamp() == false){
// 				if (etatLayer.getPlayers()[i]->getType() == state::ARCHER){
// 					etatLayer.getPlayers()[i]->setCodeTuile(4);
// 				}
// 				else if (etatLayer.getPlayers()[i]->getType() == state::BRIGAND){
// 					etatLayer.getPlayers()[i]->setCodeTuile(5);
// 				}
// 				else if (etatLayer.getPlayers()[i]->getType() == state::GUERRIER){
// 					etatLayer.getPlayers()[i]->setCodeTuile(6);
// 				}
// 				if (etatLayer.getPlayers()[i]->getType() == state::CHEVALIER){
// 					etatLayer.getPlayers()[i]->setCodeTuile(7);
// 				}
// 			}		
// 		}
		
// 		else if (etatLayer.getPlayers()[i]->getStatut() == state::ATTENTE){
// 			if (etatLayer.getPlayers()[i]->getType() == state::ARCHER){
// 				etatLayer.getPlayers()[i]->setCodeTuile(8);
// 			}
// 			else if (etatLayer.getPlayers()[i]->getType() == state::BRIGAND){
// 				etatLayer.getPlayers()[i]->setCodeTuile(9);
// 			}
// 			else if (etatLayer.getPlayers()[i]->getType() == state::GUERRIER){
// 				etatLayer.getPlayers()[i]->setCodeTuile(10);
// 			}
// 			if (etatLayer.getPlayers()[i]->getType() == state::CHEVALIER){
// 				etatLayer.getPlayers()[i]->setCodeTuile(11);
// 			}	
// 		}
		
// 		else if (etatLayer.getPlayers()[i]->getStatut() == state::MORT){
// 			etatLayer.getPlayers()[i]->setCodeTuile(12);
// 		}		
// 	}
// }