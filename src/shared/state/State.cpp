#include "State.h"

using namespace state;

State::~State(){
    ptr_clickManager = nullptr;
}

std::vector<std::vector<std::unique_ptr<MapTile>>>& State::getMap (){
    return twoDTab;
}

std::vector<std::unique_ptr<Robot>>& State::getPlayers (){
    return players;
}

void State::setRound (int newRound){
    nbRound=newRound;
}

int State::initMap (std::string map_txt){
    twoDTab={{}};
    //A compléter pour le livrable 2.0
}

bool State::getEndGame (){
    return endGame;
}

void State::setEndGame (int result){
    endGame=true;
}

int State::initClickManager (){
    ptr_clickManager=nullptr;
}

ClickManager* State::getActions (){
    return ptr_clickManager;
}

bool State::checkStatus (){
    //true si peut faire une action
    //false si stun ou mort
    for (size_t i=0; i<players.size(); i++){
        if (players[i]->getStatus()==NORMAL){
            return true;
        }
    }
    return false;
}