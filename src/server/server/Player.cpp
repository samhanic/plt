#include "../server.h"

using namespace server;
using namespace std;

// Constructor

Player::Player(string name, bool free): name(name), free(free){
}

// Getters

string Player::getName(){
    return name;
}

bool Player::getFree(){
    return free;
}