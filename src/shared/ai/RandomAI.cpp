#include "../ai.h"
#include "../engine.h"
#include "../state.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <experimental/random>

using namespace ai;
using namespace engine;
using namespace state;
using namespace std;

RandomAI::RandomAI(int nbRobot){
    this->nbRobot=nbRobot;
}

bool RandomAI::run(engine::Engine& engine){
    // L'IA effectue ces actions uniquement si c'est son tour
    if(engine.getActiveRobot()==nbRobot){
        /*Verify that the robot is still alive*/
        if(engine.getMyState()->getPlayers()[nbRobot]->getStatus()==FINAL_DEAD) return false;
        if(engine.getMyState()->getPlayers()[nbRobot]->getStatus()==STUNNED) return false;

        cout<<"Choosing 6 actions randomly to run"<<endl;
        std::array<Action, 6> actions;
        int randomNumber;
        for (int i=0;i<6;++i){
            /*Action random entre tourner et avancer*/
            randomNumber=std::experimental::randint(0,3);
            if(randomNumber==0){
                actions[i]=FORWARD;
            }
            else if (randomNumber==1){
                actions[i]=BACKWARD;
            }
            else if (randomNumber==2){
                actions[i]=ROTATION_CCLK;
            }
            else if (randomNumber==3){
                actions[i]=ROTATION_CLK;
            }
            else {
                cout <<"Problems choosing action"<<endl;
            }
        }
        engine.getMyState()->getPlayers()[nbRobot]->setRobotActions(actions);
        return true;
    }

    else return false;
}