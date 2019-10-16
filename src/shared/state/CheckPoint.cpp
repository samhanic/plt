#include "ConvBelt.h"

using namespace state;

ConvBelt::ConvBelt (ConvBeltTypeId CBTypeId){
    isEmpty=false;
    fast=false;
    CBID=CBTypeId;
}

void ConvBelt::moveRobot(Action action){
    //A compléter
}

bool const ConvBelt::isReachable(){
    return not(isEmpty);
}