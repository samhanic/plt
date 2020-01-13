#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/client/render.h"

using namespace state;
using namespace engine;
using namespace render;

BOOST_AUTO_TEST_CASE(TestEngine) {
    Engine engine;
    engine.initEngine("justIfEnableReadFile");
    engine.initEngine("../../../res/map.txt");
    engine.checkRobotsActions();
    const std::shared_ptr<state::State> ptrState = engine.getMyState();
    
    //std::array<Action,6> robactions;
    //First round
     /*robactions[0]=FORWARD;
    BOOST_CHECK_EQUAL(ptrState->getActionInRound(), 1);
    robactions[1]=BACKWARD;
    robactions[2]=ROTATION_CCLK;
    robactions[3]=ROTATION_CCLK;
    robactions[4]=ROTATION_CCLK;
    robactions[5]=ROTATION_CCLK;
    ptrState->getPlayers()[0]->setRobotActions(robactions);
    for (int i=0; i<6; i++) {
        engine.executeAction(i);
        ptrState->checkEndGame();
    }
    engine.endOfRound();
   
    //Second one
    robactions[0]=FORWARD;
    robactions[1]=ROTATION_CLK;
    robactions[2]=ROTATION_CLK;
    robactions[3]=ROTATION_CLK;
    robactions[4]=ROTATION_CLK;
    robactions[5]=FORWARD;
    ptrState->getPlayers()[0]->setRobotActions(robactions);
    for (int i=0; i<6; i++) {
        engine.executeAction(i);
        ptrState->checkEndGame();
    }
    engine.endOfRound();

    //Third one : Going to the bonus
    robactions[0]=FORWARD;
    robactions[1]=ROTATION_CLK;
    robactions[2]=ROTATION_CLK;
    robactions[3]=ROTATION_CLK;
    robactions[4]=ROTATION_CLK;
    robactions[5]=ROTATION_CLK;
    ptrState->getPlayers()[0]->setRobotActions(robactions);
    for (int i=0; i<6; i++) {
        engine.executeAction(i);
        ptrState->checkEndGame();
    }
    engine.endOfRound();

    //Fourth one : Grabbing the bonus, 
    robactions[0]=BACKWARD;
    robactions[1]=ROTATION_CCLK;
    robactions[2]=ROTATION_CCLK;
    robactions[3]=ROTATION_CCLK;
    robactions[4]=ROTATION_CCLK;
    robactions[5]=ROTATION_CLK;
    ptrState->getPlayers()[0]->setRobotActions(robactions);
    for (int i=0; i<6; i++) {
        engine.executeAction(i);
        ptrState->checkEndGame();
    }
    engine.endOfRound();

    //Fifth one : verify out of bound and 
    robactions[0]=BACKWARD;
    robactions[1]=FORWARD;
    robactions[2]=ROTATION_CCLK;
    robactions[3]=FORWARD;
    robactions[4]=ROTATION_CCLK;
    robactions[5]=BACKWARD;
    ptrState->getPlayers()[0]->setRobotActions(robactions);
    for (int i=0; i<6; i++) {
        engine.executeAction(i);
        ptrState->checkEndGame();
    }
    engine.endOfRound();
    */
}