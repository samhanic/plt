#include "CheckPoint.h"
#include <algorithm>

using namespace state;

bool CheckPoint::isVisited (Robot robot) {
    std::vector<int> v = robot.getVisitedCheckpoints();

    if (std::find(v.begin(), v.end(), checkPointFigure) != v.end()){
        return true;
    }
    return false;
}

int CheckPoint::getCheckPointFigure(){
    return checkPointFigure;
}

void CheckPoint::setCheckPointFigure (int checkPointFigure){
    this->checkPointFigure = checkPointFigure;
}
