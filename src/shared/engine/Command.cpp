#include "Command.h"
#include "../state.h"
#include "../engine.h"
#include <iostream>

using namespace engine;
using namespace state;
using namespace std;

Command::Command(state::Robot& player, int actionNumberInRound){
    //this -> player = player;
    this -> actionNumberInRound = actionNumberInRound; 
}

Command::Command(){
    
}

void Command::setPlayer(std::unique_ptr<state::Robot>& player){
    // this->player=player;
}

int Command::getActionNumberInRound() const{
    return actionNumberInRound;
}

void Command::setActionNumberInRound(int actionNumberInRound){
    this->actionNumberInRound = actionNumberInRound;
}

CommandPriority Command::getPriority() const{
    return priority;
}

void Command::setPriority(CommandPriority priority){
    this->priority = priority;
}

bool Command::executeOrder (state::State& myState){
    return 0; //If this functions executes heres,
    //there is a problem because all executeOrders should be executed in subclasses
}

bool Command::deathRobot(state::Robot& player, state::State& myState){
    //Return True if the robot is able to respawn, false if not
    if (player.getLifeNumber()==0){
        cout<<"You lost!"<<endl;
        return false;
    }
    else{
        cout<<"You loose one live"<<endl;
        player.setLifeNumber(player.getLifeNumber()-1);
        player.setLifePoints(5);
        myState.getEndRound();
        State *myStatetwo = &myState;
        //std::unique_ptr<MyClass>( new MyClass(myObject) )
        //Position posRespawn = myStatetwo->robotLastVisitedCP(std::unique_ptr<Robot>(new Robot(player)));
        // player.setPosition(posRespawn);

        //To be reviewed by professors
    }

    return true;
}