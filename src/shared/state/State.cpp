#include "../state.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <algorithm>

using namespace state;
using namespace std;

int State::initMap (std::string map_txt, MapFactory& mapFactory) {

    // L'idéal serait de déterminer longueur et largeur à partir de la map en entrée.
    int largeur = 10;
    int longueur = 10;

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
		cout << contenu << endl;
    }
    else {
		cout << "le frichier ne peut être lu" << endl;
		return -1;
	}

     // Conversion des codes des tuiles en int
    std::stringstream contenuStream(contenu);
    int i = 0, j = 0, k = 0;
    
    while(std::getline(contenuStream, code_tuile, ',')){
    	map_tuiles_code[i] = std::stoi(code_tuile);
    	i++;
    }

    // Remplissage de la grille de jeu avec les terrains
    for (i = 0; i < largeur; i++){//itération sur les lignes
    	std::vector<std::unique_ptr<MapTile>> newLigne;
    
    	for (j = 0; j < longueur; j++){//itération sur les colonnes
    		
			if (map_tuiles_code[k]>=13 && map_tuiles_code[k]<=25){//creation des convbelt
				ConvBelt newConvBelt(mapFactory.doConvertMapConvBelt()[map_tuiles_code[k]],i,j,map_tuiles_code[k]);
				std::unique_ptr<ConvBelt> ptr(new ConvBelt(newConvBelt));
				cout<<"Nouveau ConvBelt :"<<mapFactory.doConvertMapConvBelt()[map_tuiles_code[k]]<<'\t'<<"New tile Code: "<<map_tuiles_code[k]<<" -x : "<<i<<" -y : "<<j<<endl;	
				newLigne.push_back(move(ptr));
			}
			else if (map_tuiles_code[k] >= 27 && map_tuiles_code[k] <= 31){//Creation des bonus
				Bonus newBonus(mapFactory.doConvertMapBonus()[map_tuiles_code[k]], i, j, map_tuiles_code[k]);
				std::unique_ptr<Bonus> ptr(new Bonus(newBonus)) ;
				cout<<"Nouveau Bonus :"<<mapFactory.doConvertMapBonus()[map_tuiles_code[k]]<<'\t'<<"New tile Code: "<<map_tuiles_code[k]<<" -x : "<<i<<" -y : "<<j<<endl;	
				newLigne.push_back(move(ptr));
			}
			else if (map_tuiles_code[k]>=32 && map_tuiles_code[k]<=33){//creation des rotator
				Rotator newRotator(mapFactory.doConvertMapRotator()[map_tuiles_code[k]],i,j,map_tuiles_code[k]);
				std::unique_ptr<Rotator> ptr(new Rotator(newRotator));
				newLigne.push_back(move(ptr));
			}
			else if (map_tuiles_code[k]>=0 && map_tuiles_code[k]<=2){//creation des cases basiques
				Basic newBasic(mapFactory.doConvertMapBasic()[map_tuiles_code[k]],i,j,map_tuiles_code[k]);
				std::unique_ptr<Basic> ptr(new Basic(newBasic));
				newLigne.push_back(move(ptr));
			}
			else if (map_tuiles_code[k]>=3 && map_tuiles_code[k]<=7){//creation des cases basiques
				CheckPoint newCheckPoint(mapFactory.doConvertMapCheckPoint()[map_tuiles_code[k]],i,j,map_tuiles_code[k]);
				std::unique_ptr<CheckPoint> ptr(new CheckPoint(newCheckPoint));
				newLigne.push_back(move(ptr));
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

int State::initRobot (ColorStatus color) {
	Robot robot(players.size(), color);
	std::unique_ptr<Robot> ptrRR(new Robot(robot));
	players.push_back(move(ptrRR));
	
	// Gives a color to the created robot
	if (color == PINK) {
		getPlayers()[players.size() - 1]->setTileCode(0);
	} else if (color == BLUE) {
		getPlayers()[players.size() - 1]->setTileCode(1);
	} else if (color == YELLOW) {
		getPlayers()[players.size() - 1]->setTileCode(2);
	} else if (color == ORANGE) {
		getPlayers()[players.size() - 1]->setTileCode(3);
	} else if (color == RED) {
		getPlayers()[players.size() - 1]->setTileCode(4);
	}

	// Gives coordinates to the robot in function of the firt CP of the map
	getPlayers()[players.size() - 1]->setPosition(robotLastVisitedCP (getPlayers()[players.size() - 1]));
	
	cout << "new player n° "<<players.size()<<" with color "<<color<< endl;

    return 1;
}

State::~State() {
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

void State::setEndGame (int result) {Position robotLastVisitedCP (Robot& myRobot);
	endGame = result;
}

bool State::getEndRound () {
    return endRound;
}

void State::setEndRound (int result) {
	endRound = result;
}

unsigned int State::getHeightMap (std::string map_txt) {
	unsigned int numberOfLines = 0;
    std::string line;
	std::ifstream myfile(map_txt, ios::in); 
	if (myfile) {
		while (std::getline(myfile, line)) {
			++numberOfLines;
		}
		myfile.close();
		return numberOfLines;
	} else {
		cout << "le frichier ne peut être lu" << endl;
		return 0;
	}
}

unsigned int State::getWidthMap (std::string map_txt) {
	unsigned int numberOfComas = 0;
	std::string line;
	std::ifstream myfile(map_txt, ios::in);
	if (myfile){
		// Get first line
		string sLine;
		getline(myfile, sLine);
		myfile.close();
		// Count number of comas in the first line
		numberOfComas = std::count(sLine.begin(), sLine.end(), ',');
		// +1 because there is no coma at the end of a line
		return numberOfComas + 1;
    }
    else {
		cerr << "le frichier ne peut être lu" << endl;
		return -1;
	}
}

Position State::robotLastVisitedCP (std::unique_ptr<Robot>& myRobot) {
	
	int robotID = myRobot->getRobotId();

	//cout << "hello" << myRobot->getVisitedCheckpoints() << endl;
	// Recupérer la liste des checkpoints visités !!!!!!!!! pour definir les coords de sortie en fct du dernier visité

	Position pos;
	pos.setX(rand() % 9 + 1); // temporaire pour afficher plusieur robots
	pos.setY(rand() % 9 + 1);

	return pos;
}

bool State::isOccupied (const Position &myPosition) const {
	// std::vector<std::unique_ptr<Robot>> & listeRobots = state.getPlayers();
	
	// /* On compare la position de la case evaluee avec celles des robots pour
    //     savoir si une unite est dessus */
	// for(size_t i=0; i < listeRobots.size(); i++){
	// 	if (position.equals(listeRobots[i]->getPosition())){
	// 		return i;
	// 	}
	// }	
	return -1;
}
