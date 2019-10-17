#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestRobot)
{
	Robot testRobot {};
	
	testRobot.setRobotId(18);
	BOOST_CHECK_EQUAL(testRobot.getRobotId(), 18);
	testRobot.setColor(11);
	BOOST_CHECK_EQUAL(testRobot.getColor(), 11);
	testRobot.setLifePoints(2);
	BOOST_CHECK_EQUAL(testRobot.getLifePoints(), 2);
	testRobot.setLifeNumber(2);
	BOOST_CHECK_EQUAL(testRobot.getLifeNumber(), 2);
	testRobot.setOrientation(NORTH);
	BOOST_CHECK_EQUAL(testRobot.getOrientation(), NORTH);
	testRobot.setStatus(DEAD);
	BOOST_CHECK_EQUAL(testRobot.getStatus(), DEAD);
	
	
}
