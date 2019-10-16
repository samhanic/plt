<<<<<<< HEAD
#include "../state.h"

using namespace state; 
using namespace std;

void Position::setX(int newX){
    this->x=newX;
}

void Position::setY(int newY){
    this->y=newY;
=======
#include "Position.h"

using namespace state;

Position::Position(){
    x=0;
    y=0;
}

Position::Position(int x, int y){
    x=x;
    y=y;
>>>>>>> master
}

int Position::getX(){
    return x;
}

int Position::getY(){
    return y;
}
<<<<<<< HEAD
=======

void Position::setX(int newX){
    x=newX;
}

void Position::setY(int newY){
    y=newY;
}

bool Position::equals(Position& other){
    if ((other.getX()==x) and (other.getY()==y)){
            return true;
        }
    else{
        return false;
    }
}

>>>>>>> master
