#include "Position.h"

using namespace state;

Position::Position(){
    x=0;
    y=0;
}

Position::Position(int x, int y){
    x=x;
    y=y;
}

int Position::getX(){
    return x;
}

int Position::getY(){
    return y;
}

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

