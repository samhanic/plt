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

	//Thhe height and width of map is determined by the file input
    int width;
    int height;

	unsigned int numberOfLines = 0;
	unsigned int numberOfComas = 0;
    std::string line;
	std::string lineS;
	std::ifstream myfile(map_txt, ios::in); 

	if (myfile) {
		/* Calculate width */
		std::getline(myfile, lineS);
		numberOfComas = std::count(lineS.begin(), lineS.end(), ',');
		/* +1 because there is no coma at the end of a line */
		height = numberOfComas + 1;

		/* Calculate height */
		while (std::getline(myfile, line)) {
			++numberOfLines;
		}
		width = numberOfLines + 1;		
		myfile.close();
	} else {
		cout << "Unable to read the file" << endl;
		return 0;
	}
	this->mapHeight = height;
	this->mapWidth = width;

    std::ifstream fichier(map_txt, ios::in);    
    std::string contenu, ligne, code_tuile;
    
    int map_tuiles_code[mapWidth * mapHeight];
    
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
		cout << "le fichier ne peut être lu" << endl;
		return -1;
	}

     /* Convert tiles into int*/
    std::stringstream contenuStream(contenu);
    int i = 0, j = 0, k = 0;
    
    while(std::getline(contenuStream, code_tuile, ',')){
    	map_tuiles_code[i] = std::stoi(code_tuile);
    	i++;
    }

    /* Fill the tab with diferent tiles */
    for (i = 0; i < mapWidth; i++){
    	std::vector<std::unique_ptr<MapTile>> newLigne;
    	for (j = 0; j < mapHeight; j++){
    		
			if (map_tuiles_code[k]>=13 && map_tuiles_code[k]<=25){//create convbelt
				ConvBelt newConvBelt(mapFactory.doConvertMapConvBelt()[map_tuiles_code[k]],i,j,map_tuiles_code[k]);
				std::unique_ptr<ConvBelt> ptr(new ConvBelt(newConvBelt));
				cout<<"Nouveau ConvBelt :"<<newConvBelt.getConvBeltTypeId()<<'\t'<<"New tile Code: "<<map_tuiles_code[k]<<" with x : "<<i<<" and y : "<<j<<endl;	
				newLigne.push_back(move(ptr));
			}
			else if (map_tuiles_code[k] >= 27 && map_tuiles_code[k] <= 31){//create bonus
				Bonus newBonus(mapFactory.doConvertMapBonus()[map_tuiles_code[k]], i, j, map_tuiles_code[k]);
				std::unique_ptr<Bonus> ptr(new Bonus(newBonus)) ;
				cout<<"Nouveau Bonus :"<<mapFactory.doConvertMapBonus()[map_tuiles_code[k]]<<'\t'<<"New tile Code: "<<map_tuiles_code[k]<<" with x : "<<i<<" and y : "<<j<<endl;	
				newLigne.push_back(move(ptr));
			}
			else if (map_tuiles_code[k]>=32 && map_tuiles_code[k]<=33){//create rotator
				Rotator newRotator(mapFactory.doConvertMapRotator()[map_tuiles_code[k]],i,j,map_tuiles_code[k]);
				std::unique_ptr<Rotator> ptr(new Rotator(newRotator));
				cout<<"Nouveau Rotator :"<<mapFactory.doConvertMapRotator()[map_tuiles_code[k]]<<'\t'<<"New tile Code: "<<map_tuiles_code[k]<<" with x : "<<i<<" and y : "<<j<<endl;
				newLigne.push_back(move(ptr));
			}
			else if (map_tuiles_code[k]>=0 && map_tuiles_code[k]<=2){//create basics
				Basic newBasic(mapFactory.doConvertMapBasic()[map_tuiles_code[k]],i,j,map_tuiles_code[k]);
				std::unique_ptr<Basic> ptr(new Basic(newBasic));
				newLigne.push_back(move(ptr));
			}
			else if (map_tuiles_code[k]>=3 && map_tuiles_code[k]<=7){//create checkpoints
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
	
	/* Gives a color to the created robot */
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

	/* Gives coordinates to the robot in function of the firt CP of the map */
	getPlayers()[players.size() - 1]->setPosition(robotLastVisitedCP (*getPlayers()[players.size() - 1]));
	
	cout << "new player n° "<<players.size()<<" with color "<<color<< endl;

    return 1;
}

State::~State() {
}

const std::vector<std::vector<std::unique_ptr<MapTile>>>& State::getMap () const {
	return twoDTab;
}

std::vector<std::unique_ptr<Robot>>& State::getPlayers () {
    vector<unique_ptr<Robot>> & refRobots = players;
	//cout<<(this->robotLastVisitedCP(refRobots[0])).getX()<<"robotlastvisited executed"<<endl;
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

void State::checkEndGame () {
	/* Gets cp on the map */
	std::vector<int> cpOnTheMap;
	for (int i = 0 ; i < mapHeight ; i++) {
		for (int j = 0 ; j < mapWidth ; j++) {
			if (twoDTab[i][j]->getTileCode() >= 3 && twoDTab[i][j]->getTileCode() <= 7 ) {
				cpOnTheMap.push_back(twoDTab[i][j]->getTileCode()-2);
			}
		}
	}

	/* Compares with cp validated by players */
	for (unsigned int i = 0 ; i < players.size() ; i++) {
		std::vector<int> cpOfPlayer = getPlayers()[i]->getVisitedCheckpoints();
		std::sort(cpOfPlayer.begin(), cpOfPlayer.end());
		std::sort(cpOnTheMap.begin(), cpOnTheMap.end());
		if (cpOnTheMap == cpOfPlayer) {
			this->endGame = true;
		}
		for (unsigned int i = 0; i < cpOnTheMap.size() ; i++) {
			cout<<"CP MAP : "<<cpOnTheMap[i]<<" CP PLAYER : "<<cpOfPlayer[i]<<endl;
		}
	}
}

bool State::getEndRound () {
    return endRound;
}

void State::setEndRound (int result) {
	endRound = result;
}

int State::getMapHeight() const {
	return mapHeight;
}
void State::setMapHeight(int mapHeight) {
	this->mapHeight = mapHeight;
}
int State::getMapWidth() const {
	return mapWidth;
}
void State::setMapWidth(int mapWidth) {
	this->mapWidth = mapWidth;
}

Position State::robotLastVisitedCP (Robot& myRobot) {
	
	//int robotID = myRobot.getRobotId();
	std::vector<int> visitedPC = myRobot.getVisitedCheckpoints();
	
	Position positionOfLastCp;

	/* Get value of last visited checkpoint */
	int tempMaxCP = 0;
	bool tempCpFound = 0;
	for (unsigned int i = 0 ; i < visitedPC.size() ; i++) {
		if (tempMaxCP <= visitedPC[i]) {
			tempMaxCP = visitedPC[i];
		}
	}
	cout<<"The temp max : "<<tempMaxCP<<endl;

	cout<<"width : "<<mapWidth<<"height : "<<mapHeight<<endl;
	/* Get coordinates of las visited checkpoints */
	for (int i = 0 ; i < mapWidth ; i++){ 
    	for (int j = 0 ; j < mapHeight ; j++){
			//cout<<twoDTab[i][j]->getTileCode()<<endl;
			if (twoDTab[i][j]->getTileCode() == (tempMaxCP + 2)) {
				positionOfLastCp.setX(j);
				positionOfLastCp.setY(i);	
				tempCpFound = 1;			
			}
		}
	}
	/* if no cp found left up corner */
	if (tempCpFound == 0) {
		positionOfLastCp.setX(0);
		positionOfLastCp.setY(0);
	}

	//cout << "hello" << myRobot->getVisitedCheckpoints() << endl;
	//pos.setX(rand() % 9 + 1); // get random coordiantes to debug
	//pos.setY(rand() % 9 + 1);
	
	return positionOfLastCp;
}

bool State::isOccupied (const Position &myPosition) const {
	//std::vector<std::unique_ptr<Robot>> & listeRobots = getPlayers();
	
	// /* On compare la position de la case evaluee avec celles des robots pour
    //     savoir si une unite est dessus */
	// for(size_t i=0; i < listeRobots.size(); i++){
	// 	if (position.equals(listeRobots[i]->getPosition())){
	// 		return i;
	// 	}
	// }	
	return false;
}

bool State::deathRobot (Robot& myRobot){
    //Return True if the robot is able to respawn, false if not
	std::array<Action, 6> actionSlotTab;
	for (int i=0 ; i<6 ; i++) {
		actionSlotTab[i] = ACTION_FORBIDDEN;
	}
	myRobot.setRobotActions(actionSlotTab);
	
    if (myRobot.getLifeNumber()==0){
        cout<<"You lost!"<<endl;
        myRobot.setStatus(FINAL_DEAD);
        return false;
    }
    else{
        cout<<"You loose one live"<<endl;
        myRobot.setLifeNumber(myRobot.getLifeNumber()-1);
        myRobot.setLifePoints(5);
		myRobot.setOrientation(NORTH);
        Position posRespawn = robotLastVisitedCP(myRobot);
        myRobot.setPosition(posRespawn);
        return true;
    }
}
