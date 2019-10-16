#include "../state.h"

using namespace state; 

Element::Element() {
	position.setX(0);
	position.setY(0);
}

void Element::initElement() {
    this->position.setX(0);
    this->position.setY(0);
}

state::Position Element::getPosition () {
    return position;
}




