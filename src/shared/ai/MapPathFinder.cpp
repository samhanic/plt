#include "../ai.h"
#include "../engine.h"
#include "../state.h"
#include "../../client/render.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

#define GETX getPlayers()[robotNumber]->getPosition().getX()
#define GETY getPlayers()[robotNumber]->getPosition().getY()
#define GETORIENTATION getPlayers()[robotNumber]->getOrientation()

using namespace ai;
using namespace engine;
using namespace state;
using namespace render;
using namespace std;

state::Position MapPathFinder::nearestCP (state::State& myState, int robotNumber){
    //Find all the CP not visited yet
    std::vector<Position> posCP;
    std::vector<int> nbCP; //for debug
    for (size_t x=0; x<myState.getMap().size() ; ++x){
        for (size_t y=0 ; y<myState.getMap()[0].size() ; ++y){
            if (myState.getMap()[x][y]->getIdStatic()==CHECKPOINT){
                //cout<<"Checkpoint in x = "<<x<<"and y = "<<y<<" is checked"<<endl;
                CheckPoint *cp = static_cast<CheckPoint*> (myState.getMap()[x][y].get());
                if (cp->isVisited(*myState.getPlayers()[robotNumber])==false){
                    posCP.insert(posCP.end(),cp->getPosition());
                    nbCP.insert(nbCP.end(),cp->getCheckPointFigure());//for debug
                }
            }
        }
    }
    //cout<<posCP.size()<<"cp not yet visited"<<endl;
    
    //Find the nearest in all these
    int nearestCP=-1;
    int distanceNearestCP=100;
    int distance;
    for (size_t i=0; i<posCP.size(); ++i){
        distance = 0;
        distance += abs(posCP[i].getX()-myState.GETY);
        distance += abs(posCP[i].getY()-myState.GETX);
        //cout<<"Distance for checkpoint nb "<<nbCP[i]<<" is "<<distance<<endl;
        if (distance<distanceNearestCP && distance!=0){
            nearestCP=static_cast<int>(i);
            distanceNearestCP=distance;
        }
    }
    if (nearestCP==-1){
        cout<<"Trying to find nearest CP but all the CP have already been visited!"<<endl;
        return posCP[0];
    }
    //cout<<"nearestCP number : "<<nearestCP<<endl;
    //cout<<"The nearest checkpoint is located in x = "<<posCP[nearestCP].getX()<<"and y = "<<posCP[nearestCP].getY()<<endl;
    return posCP[nearestCP];
}

std::array<state::Action, 6> MapPathFinder::pathToNearestCp (state::State& myState, int robotNumber){
    std::array<state::Action, 6> solution;
    Position objective = nearestCP(myState,robotNumber);

    int y = myState.getPlayers()[robotNumber]->getPosition().getX();
    int x = myState.getPlayers()[robotNumber]->getPosition().getY();
    //cout<<"Now the robot is located in "<<x<<" "<<y<<endl;
    //state::DirectionStatus dir = myState.getPlayers()[robotNumber]->getOrientation();

    int nbboost=1;
    for (int i=0;i<6;i++){
        if (x<objective.getX()){
            solution[i]=BACKWARD;
            //cout<<"Solution : backward for action nb "<<i<<endl;
            x++;
        }
        else if (x>objective.getX()){
            solution[i]=FORWARD;
            //cout<<"Solution : forward for action nb "<<i<<endl;
            x--;
        }
        else if (x+1 == objective.getX()){
            //cout<<"Solution : 1 right for next checkpoint for action nb "<<i<<endl;
            solution[i]=ROTATION_CLK;
            solution[i+1]=FORWARD;
            i++;
        }
        else if (abs(objective.getY()-y)!=nbboost && i!=5){
            solution[i]=BOOSTER;
            //cout<<"Solution : boost for action nb "<<i<<endl;
            nbboost++;
        }
        else if (y<objective.getY()){
            solution[i]=RIGHT;
            y+=nbboost;
            nbboost=1;
            //cout<<"Solution : right for action nb "<<i<<endl;
        }
        else if (y>objective.getY()){
            solution[i]=LEFT;
            y-=nbboost;
            nbboost=1;
            //cout<<"Solution : left for action nb "<<i<<endl;
        }
        else if (x==objective.getX() && y==objective.getY()) {
            //cout<<"Solution : check the next cp for action nb "<<i<<endl;
            objective = nearestCP(myState,robotNumber);
            solution[i]=NO_ACTION;
            //i--;
        }
    }
    //cout<<"The actions for this turn have been fixed : "<<solution[0]<<solution[1]<<solution[2]<<solution[3]<<solution[4]<<solution[5]<<endl;
    return solution;
}

std::vector<state::Action> dijkstra (state::State& myState, int robotNumber, int wantedX, int wantedY){
    //std::unique_ptr<state::State> tempState = make_unique<state::State>(myState); Does not works because of cpp version 11
    //std::unique_ptr<Robot>& ptrRobot = state.getPlayers()[0];
    //State *state = new State();
    //std::shared_ptr<State> ptrState(state);
    // state::State *tempState = new State();
    // std::shared_ptr<State> ptrState

    // std::shared_ptr<state::State> tempState;
    // tempState = std::make_shared<state::State> (myState);
    
    // struct datastates{
    //     std::unique_ptr<state::State> st;
    //     int x;
    //     int y;
    //     int nbActions;
    //     int rotation;
    //     bool modified;
    //     std::vector<state::Action> sol;
    // };
    // //Initialization
    // std::vector<std::vector<datastates[4]>> states;
    // for (int i=0; i<myState.getMapHeight();++i){
    //     for (int j=0;j<myState.getMapWidth();++j){
    //         for (int k=0;k<4;++k){
    //             states[i][j][k].x=i;
    //             states[i][j][k].y=j;
    //             states[i][j][k].nbActions=100;
    //             states[i][j][k].modified=false;
    //         }
    //     }
    // }

    // //states[myState.GETX][myState.GETY][myState.GETORIENTATION].st=std::make_unique<state::State>(myState);
    // states[myState.GETX][myState.GETY][myState.GETORIENTATION].st=std::unique_ptr<state::State>(new state::State(myState));
    // states[myState.GETX][myState.GETY][myState.GETORIENTATION].modified=true;
    // states[myState.GETX][myState.GETY][myState.GETORIENTATION].nbActions=0;
    
    // int i,j,k,rotProv;
    // bool notfinished;
    // //Loop
    // do{
    //     notfinished=true;
    //     for (i=0; i<myState.getMapHeight();++i){
    //         for (j=0;j<myState.getMapWidth();++j){
    //             for (k=0; k<4; ++k){
    //                 if (states[i][j][k].modified){
    //                     notfinished=false;
    //                     states[i][j][k].modified=false;


    //                     // //Forward
    //                     // engine::Move action (robotNumber,FORWARD);
    //                     // tempState=std::make_shared<state::State>(states[i][j][k].st);
    //                     // action.executeOrder(tempState);
    //                     // if (states[tempState->GETX][tempState->GETY][k].nbActions>states[i][j][k].nbActions+1){
    //                     //     states[tempState->GETX][tempState->GETY][k].st=std::make_unique<state::State>(tempState);
    //                     //     states[tempState->GETX][tempState->GETY][k].sol.push_back(FORWARD);
    //                     // }
    //                     // //Backward
    //                     // engine::Move action (robotNumber,BACKWARD);
    //                     // tempState=std::make_shared<state::State>(states[i][j][k].st);
    //                     // action.executeOrder(tempState);
    //                     // if (states[tempState->GETX][tempState->GETY][k].nbActions>states[i][j][k].nbActions+1){
    //                     //     states[tempState->GETX][tempState->GETY][k].st=std::make_unique<state::State>(tempState);
    //                     //     states[tempState->GETX][tempState->GETY][k].sol.push_back(BACKWARD);
    //                     // }
    //                     // //Rotation clk
    //                     // engine::Rotation action (robotNumber,ROTATION_CLK);
    //                     // tempState=std::make_shared<state::State>(states[i][j][k].st);
    //                     // action.executeOrder(tempState);
    //                     // rotProv=k+1;
    //                     // if (rotProv==5) rotProv = 1;
    //                     // if (states[i][j][k].nbActions>states[i][j][rotProv].nbActions+1){
    //                     //     states[tempState->GETX][tempState->GETY][k].st=std::make_unique<state::State>(tempState);
    //                     //     states[tempState->GETX][tempState->GETY][k].sol.push_back(BACKWARD);
                        
    //             }
    //         }
    //     }
    // }
    // } while (notfinished);

    // int miniActions=1000;
    // for (k=0;k<4;k++){
    //     if (states[wantedX][wantedY][k].nbActions<miniActions){
    //         miniActions=states[wantedX][wantedY][k].nbActions;
    //     }
    // }
    // for (k=0;k<4;k++){
    //     if (states[wantedX][wantedY][k].nbActions==miniActions){
    //         return states[wantedX][wantedY][k].sol;
    //     }
    // }
    cout<<"Path not found!"<<endl;
    std::vector<state::Action> facticeSol;
    return facticeSol;
}
