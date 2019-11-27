#include "../ai.h"
#include "../engine.h"
#include "../state.h"
#include "../../client/render.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

using namespace ai;
using namespace engine;
using namespace state;
using namespace render;
using namespace std;

int MapPathFinder::nearestCP (engine::Engine& myEngine) {

    int myRobotId = 1;

    int nbCp = 5;
    int posCp[nbCp][3];
    int indice = 0;

    for (int i = 0 ; i < myEngine.getMyState()->getMapWidth() ; i++){ 
    	for (int j = 0 ; j <  myEngine.getMyState()->getMapHeight() ; j++){
			//cout<<twoDTab[i][j]->getTileCode()<<endl;
			if (myEngine.getMyState()->getMap()[i][j]->getTileCode() <=3 &&
            myEngine.getMyState()->getMap()[i][j]->getTileCode() >=7) {
				posCp[indice][0]=  myEngine.getMyState()->getMap()[i][j]->getTileCode();
                posCp[indice][1]= i;
                posCp[indice][2]= j;
                indice ++;
                //cout<<		
			}
		}
	}


    bool flagVisited = false;

    int oldTempXDiff = myEngine.getMyState()->getMapWidth();
    int oldTempYDiff = myEngine.getMyState()->getMapHeight();
    int tempXDiff = 0;
    int tempYDiff = 0;
    int tempNearestCp = 1;


        
    std::vector<int> tabVisitedCp (myEngine.getMyState()->getPlayers().size());
    tabVisitedCp =  myEngine.getMyState()->getPlayers()[myRobotId]->getVisitedCheckpoints();
    
    for(int y = 0 ; y < 5 ; y++) {
        for(unsigned int j = 0 ; j < tabVisitedCp.size() ; j++ ) {
            if (posCp[y][0] == tabVisitedCp[j]) {
                flagVisited = true;
            }
        }
        if (flagVisited == false) { // If not visited let's calculat distance
            /* Calculate X distance */
            if ((myEngine.getMyState()->getPlayers()[myRobotId]->getPosition().getX()- posCp[y][1]) < 0){
                tempXDiff = posCp[y][1] - myEngine.getMyState()->getPlayers()[myRobotId]->getPosition().getX();
            } else {
                tempXDiff = myEngine.getMyState()->getPlayers()[myRobotId]->getPosition().getX()- posCp[y][1];
            }
            /* Calculate Y distance */
            if ((myEngine.getMyState()->getPlayers()[myRobotId]->getPosition().getY()- posCp[y][2]) < 0){
                tempYDiff = posCp[y][2] - myEngine.getMyState()->getPlayers()[myRobotId]->getPosition().getY();
            } else {
                tempYDiff = myEngine.getMyState()->getPlayers()[myRobotId]->getPosition().getY()- posCp[y][2];
            }

            if ((tempXDiff + tempYDiff) < (oldTempXDiff + oldTempYDiff)) {
                oldTempXDiff = tempXDiff;
                oldTempYDiff = tempYDiff;
                tempNearestCp = posCp[y][0];
            }  
        }
        flagVisited = false;  
    }
    cout<<"not visited nearest cp is : "<<tempNearestCp<<endl;
    return tempNearestCp;
}
