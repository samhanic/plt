#include "../state.h"
/*
using namespace state;

Robot::Robot(int id, int color){
    robotId=id;
    color=color;
    visitedCheckpoints=[1];
    lifePoints=5;
    lifeNumber=3;
    orientation=NORTH;
    isBoosted=0;
    status=NORMAL;
    ownsHeal=false;
    ownsAutoAttack=false;
    ownsShield=false;
    ownsCrossAttack=false;
    ownsBomb=false;
    activatedAutoAttack=false;
    activatedShied=false;
}

bool Robot::isStatic(){
    return false;
}

void Robot::doAction(Action action){
    if action==FORWARD{
        if orientation==EAST{
            setY(getY()+1);
        }
        if orientation==NORTH{
            setX(getX()-1);
        }
        if orientation==WEST{
            setY(getY()-1);
        }
        if orientation==SOUTH{
            setX(getX()+1);
        }
    }
    if action==BACKWARD{
        if orientation==EAST{
            setY(getY()-1);
        }
        if orientation==NORTH{
            setX(getX()+1);
        }
        if orientation==WEST{
            setY(getY()+1);
        }
        if orientation==SOUTH{
            setX(getX()-1);
        }
    }
    if action==LEFT{
        if isBoosted!=0{
            if orientation==NORTH{
                setY(getY()-isBoosted);
                isBoosted=0;
            }
            if orientation==EAST{
                setX(getX()-isBoosted);
                isBoosted=0;
            }
            if orientation==SOUTH{
                setY(getY()+isBoosted);
                isBoosted=0;
            }
            if orientation==WEST{
                setX(getX()+isBoosted);
                isBoosted=0;
            }
        }
        else {
            if orientation==EAST{
                orientation=NORTH;
            }
            if orientation==NORTH{
                orientation=WEST;
            }
            if orientation==WEST{
                orientation=SOUTH;
            }
            if orientation==SOUTH{
                orientation=EAST;
            }
        }
    }
    if action==RIGHT{
        if isBoosted!=0{
            if orientation==NORTH{
                setY(getY()+isBoosted);
                isBoosted=0;
            }
            if orientation==EAST{
                setX(getX()+isBoosted);
                isBoosted=0;
            }
            if orientation==SOUTH{
                setY(getY()-isBoosted);
                isBoosted=0;
            }
            if orientation==WEST{
                setX(getX()-isBoosted);
                isBoosted=0;
            }
        }
        else {
            if orientation==EAST{
                orientation=SOUTH;
            }
            if orientation==NORTH{
                orientation=EAST;
            }
            if orientation==WEST{
                orientation=NORTH;
            }
            if orientation==SOUTH{
                orientation=WEST;
            }
        }
    }
    if action==BOOSTER{
        isBoosted++;
    }
    if action==B_HEAL{
        lifePoints=5;
    }
    if action==B_AUTOATTACK{
        ownsAutoAttack=false;
        ownsAutoAttack=true;
    }
    if action==B_CROSSFIRE{
        ownsCrossAttack=false;
    }
    if action==B_SHIELD{
        ownsShield=false;
        activatedShield=true;
    }
    if action==B_BOMBE{
        ownsBomb=false;
        dropBomb(getX(),getY());
    }
    if (action==DELETE_I or action==DELETE_II or action==DELETE_III 
        or action==DELETE_IV or action==DELETE_V or action==DELETE_VI){
        getAction(action);
    }
}

void Robot::getDamage(int damage){
    if lifePoints>damage{
        lifePoints-=damage;
    }
    else{
        deathRobot();
    }
}

void Robot::deathRobot(){
    if lifeNumber!={
        lifeNumber--;
    }
    else{
        ActionStatus=DEAD;
    }
}*/
