#include "../state.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace state;
using namespace std;

int State::initMap (std::string map_txt) {

    // L'idéal serait de déterminer longueur et largeur à partir de la map en entrée.
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
    }
    else {return -1;}

     // Conversion des codes des tuiles en int
    std::stringstream contenuStream(contenu);
    int i = 0, j = 0, k = 0;
    
    while(std::getline(contenuStream, code_tuile, ',')){
    	map_tuiles_code[i] = std::stoi(code_tuile);
    	i++;
    }

    // Remplissage de la grille de jeu avec les terrains
    for (i = 0; i < largeur; i++){
    	std::vector<std::unique_ptr<MapTile>> newLigne;
    
    	for (j = 0; j < longueur; j++){
    		if (map_tuiles_code[k] >= 0 && map_tuiles_code[k] <= 46){
                // Recherche à determiner type de tuile : à coder 
                /*
				if (correspondances.getCorrespondanceTP().find(map_tuiles_code[k]) != correspondances.getCorrespondanceTP().end()){
					TerrainPraticable newTP(correspondances.getCorrespondanceTP()[map_tuiles_code[k]],i,j,map_tuiles_code[k]);
					std::unique_ptr<TerrainPraticable> ptr(new TerrainPraticable(newTP)) ;
					newLigne.push_back(move(ptr));
				}

				else if (correspondances.getCorrespondanceTNP().find(map_tuiles_code[k]) != correspondances.getCorrespondanceTNP().end()){
					TerrainNonPraticable newTNP(correspondances.getCorrespondanceTNP()[map_tuiles_code[k]],i,j,map_tuiles_code[k]);
					std::unique_ptr<TerrainNonPraticable> ptr(new TerrainNonPraticable(newTNP)) ;
					newLigne.push_back(move(ptr));
				}
				*/
			}
    		else{
    			cerr << "Code Tuile " << map_tuiles_code[k]<< " invalide dans le fichier " << map_txt << endl;
    			return 0;
    		
    		}
    		
    		k++;
    	}
    	twoDTab.push_back(move(newLigne));
    }    
    return 1;
}

int State::initRobot () {
    // Add parameter to choose wich robot to create 
    Robot blueRobot(players.size() + 1, BLUE);
	std::unique_ptr<Robot> ptrBR(new Robot(blueRobot));
	players.push_back(move(ptrBR));

    Robot yellowRobot(players.size() + 1, YELLOW);
	std::unique_ptr<Robot> ptrYR(new Robot(yellowRobot));
	players.push_back(move(ptrYR));

    Robot pinkRobot(players.size() + 1, PINK);
	std::unique_ptr<Robot> ptrPR(new Robot(pinkRobot));
	players.push_back(move(ptrPR));

    Robot orangeRobot(players.size() + 1, ORANGE);
	std::unique_ptr<Robot> ptrOR(new Robot(orangeRobot));
	players.push_back(move(ptrOR));

    Robot redRobot(players.size() + 1, RED);
	std::unique_ptr<Robot> ptrRR(new Robot(redRobot));
	players.push_back(move(ptrRR));

    return 1;
}

int State::initClickManager () {
    ptr_clickManager = nullptr;
	ptr_clickManager = new ClickManager();
	return 1;
}

State::~State() {
	delete ptr_clickManager;
	ptr_clickManager = nullptr;
}

std::vector<std::vector<std::unique_ptr<MapTile>>>& State::getMap () {
    vector<vector<unique_ptr<MapTile>>> & refMap = twoDTab;
	return refMap;
}

std::vector<std::unique_ptr<Robot>>& State::getPlayers () {
    vector<unique_ptr<Robot>> & refRobots = players;
	return refRobots;
}

int State::getActionInRound () {
    return actionInRound;
}

void State::setActionInRound (int newAction) {
    actionInRound = newAction;
}

bool State::getEndGame () {
    return endGame;
}

void State::setEndGame (int result) {
	endGame = result;
}

bool State::getEndRound () {
    return endRound;
}

void State::setEndRound (int result) {
	endRound = result;
}

ClickManager* State::getActions () {
    return ptr_clickManager;
}
