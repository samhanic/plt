#include "../state.h"
#include <iostream>

using namespace std;
using namespace state; 

void Position::setX(int newX) {
	if (newX >= 0) {
		this->x=newX;
	} else {
		cout <<  "X is outside of the map";
	}
}

void Position::setY(int newY) {
	if (newY >= 0) {
		this->y=newY;
	} else {
		cout <<  "Y is outside of the map";
	}
}

int Position::getX() {
    return x;
}

int Position::getY() {
    return y;
}
