#include "../state.h"

using namespace state; 
using namespace std;

void Position::setX(int newX){
    this->x=newX;
}

void Position::setY(int newY){
    this->y=newY;
}

int Position::getX(){
    return x;
}

int Position::getY(){
    return y;
}
