#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include "../../src/shared/engine.h"
#include "../../src/client/render.h"

using namespace state;
using namespace engine;
using namespace render;

BOOST_AUTO_TEST_CASE(TestEngine) {
    Engine engine;
    engine.initEngine();
    engine.checkRobotsActions();
    const std::shared_ptr<state::State> ptrState = engine.getMyState();
    unsigned int width = ptrState->getMapWidth();
   	unsigned int height = ptrState->getMapHeight();

    std::array<Action,6> robactions;
    robactions[0]=FORWARD;
    robactions[1]=BACKWARD;
    robactions[2]=ROTATION_CCLK;
    robactions[3]=ROTATION_CLK;
    robactions[4]=ACTION_FORBIDDEN;
    robactions[5]=NO_ACTION;
    ptrState->getPlayers()[0]->setRobotActions(robactions);
    //engine.executeAction(0);
    //engine.checkHole();
}