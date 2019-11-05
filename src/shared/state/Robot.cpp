#include "../state.h"

using namespace state;

Robot::Robot(){
    robotId=0;
    color=BLUE;
}

Robot::Robot(int id, ColorStatus color){
    robotId=id;
    color=color;
}

bool Robot::isStatic(){
    return false;
}

int Robot::getRobotId() const{
    return robotId;
}

void Robot::setRobotId(int robotId){
    this->robotId = robotId;
}

ColorStatus Robot::getColor() const{
    return color;
}

void Robot::setColor(ColorStatus color){
    this->color = color;
}

const std::vector<int>& Robot::getVisitedCheckpoints() const{
    return visitedCheckpoints;
}

void Robot::setVisitedCheckpoints(const std::vector<int>& visitedCheckpoints){
    this->visitedCheckpoints = visitedCheckpoints;
}
    
void Robot::setRobotActions(const std::array<Action, 6>& robotActions){
    this -> robotActions = robotActions;
}

const std::array<Action, 6>& Robot::getRobotActions() const {
    return robotActions;
}

int Robot::getLifePoints() const{
    return lifePoints;
}

void Robot::setLifePoints(int lifePoints){
    this->lifePoints = lifePoints;
}

int Robot::getLifeNumber() const{
    return lifeNumber;
}

void Robot::setLifeNumber(int lifeNumber){
    this->lifeNumber = lifeNumber;
}

DirectionStatus Robot::getOrientation() const{
    return orientation;
}

void Robot::setOrientation(DirectionStatus orientation){
    this->orientation=orientation;
}

int Robot::getIsBoosted() const{
    return isBoosted;
}

void Robot::setIsBoosted(int isBoosted){
    this->isBoosted = isBoosted;
}

ActionStatus Robot::getStatus() const{
    return status;
}

void Robot::setStatus(ActionStatus status){
    this->status = status;
}

const std::array<bool,5>& Robot::getBonusOwned() const{
    return bonusOwned;
}

void Robot::setBonusOwned(const std::array<bool,5>& bonusOwned){
    this->bonusOwned = bonusOwned;
}

const std::array<bool,2>& Robot::getBonusActivated() const{
    return bonusActivated;
}

void Robot::setBonusActivated(const std::array<bool,2>& bonusActivated){
    this->bonusActivated = bonusActivated;
}
