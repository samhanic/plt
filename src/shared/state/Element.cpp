#include "Element.h"

using namespace state;

Element::Element(){
    position.setX(0);
    position.setY(0);
}

TypeId Element::getIdStatic() {
    return idStatic;
};

bool Element::isStatic(){
    if (idStatic==ROBOT) {
        return true
    }
    else{
        return false
    }
}
