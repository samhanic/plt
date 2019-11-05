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

// void Robot::doAction(Action action){
//     if (action==FORWARD){
//         if (orientation==EAST){
//             position.setY(position.getY()+1);
//         }
//         if (orientation==NORTH){
//             position.setX(position.getX()-1);
//         }
//         if (orientation==WEST){
//             position.setY(position.getY()-1);
//         }
//         if (orientation==SOUTH){
//             position.setX(position.getX()+1);
//         }
//     }
//     if (action==BACKWARD){
//         if (orientation==EAST){
//             position.setY(position.getY()-1);
//         }
//         if (orientation==NORTH){
//             position.setX(position.getX()+1);
//         }
//         if (orientation==WEST){
//             position.setY(position.getY()+1);
//         }
//         if (orientation==SOUTH){
//             position.setX(position.getX()-1);
//         }
//     }
//     if (action==LEFT){
//         if (isBoosted!=0){
//             if (orientation==NORTH){const std::array<Action, 6>& getRobotActions() const;
//                 position.setY(position.getY()-isBoosted);
//                 isBoosted=0;
//             }
//             if (orientation==EAST){
//                 position.setX(position.getX()-isBoosted);
//                 isBoosted=0;
//             }
//             if (orientation==SOUTH){
//                 position.setY(position.getY()+isBoosted);
//                 isBoosted=0;
//             }
//             if (orientation==WEST){
//                 position.setX(position.getX()+isBoosted);
//                 isBoosted=0;
//             }
//         }
//         else {
//             if (orientation==EAST){
//                 orientation=NORTH;
//             }
//             if (orientation==NORTH){
//                 orientation=WEST;
//             }
//             if (orientation==WEST){
//                 orientation=SOUTH;
//             }
//             if (orientation==SOUTH){
//                 orientation=EAST;
//             }
//         }
//     }
//     if (action==RIGHT){
//         if (isBoosted!=0){
//             if (orientation==NORTH){
//                 position.setY(position.getY()+isBoosted);
//                 isBoosted=0;
//             }
//             if (orientation==EAST){
//                 position.setX(position.getX()+isBoosted);
//                 isBoosted=0;
//             }
//             if (orientation==SOUTH){
//                 position.setY(position.getY()-isBoosted);
//                 isBoosted=0;
//             }
//             if (orientation==WEST){
//                 position.setX(position.getX()-isBoosted);
//                 isBoosted=0;
//             }
//         }
//         else {
//             if (orientation==EAST){
//                 orientation=SOUTH;
//             }
//             if (orientation==NORTH){
//                 orientation=EAST;
//             }
//             if (orientation==WEST){
//                 orientation=NORTH;
//             }
//             if (orientation==SOUTH){
//                 orientation=WEST;
//             }
//         }
//     }
//     if (action==BOOSTER){
//         isBoosted++;
//     }
//     if (action==B_HEAL){
//         lifePoints=5;
//     }
//     if (action==B_AUTOATTACK){
//         ownsAutoAttack=false;
//         ownsAutoAttack=true;
//     }
//     if (action==B_CROSSFIRE){
//         ownsCrossAttack=false;
//     }
//     if (action==B_SHIELD){
//         ownsShield=false;
//         activatedShied=true;
//     }
//     if (action==B_BOMBE){
//         ownsBomb=false;
//         //dropBomb(position.getX(),position.getY());
//     }
//     if (action==DELETE_I or action==DELETE_II or action==DELETE_III 
//         or action==DELETE_IV or action==DELETE_V or action==DELETE_VI){
//         //getAction(action);
//     }
// }

// void Robot::getDamage(int damage){
//     if (lifePoints>damage){
//         lifePoints-=damage;
//     }
//     else{
//         deathRobot();
//     }
// }

// void Robot::deathRobot(){
//     if (lifeNumber!=1){
//         lifeNumber--;
//     }
//     else{
//         status=DEAD;
//     }
// }
