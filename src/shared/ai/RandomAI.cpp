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

void RandomAI::run(engine::Engine& engine){
    // L'IA effectue ces actions uniquement si c'est son tour
    //if(engine.getActiveRobot()==nbRobot){
        /*Action random entre tourner et avancer*/
        cout<<"Random action will be drawed"<<endl;
        std::array<Action, 6> actions;
        int randomNumber;
        for (int i=0 ; i<6 ; ++i){
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
        }
        engine.getMyState()->getPlayers()[1]->setRobotActions(actions);
    //}
}