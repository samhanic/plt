#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include <bits/stdc++.h> 
using namespace std; 

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestState)
{
	State testState {};

    testState.setActionInRound(15);
    BOOST_CHECK_EQUAL(testState.getActionInRound(),15);
	
    testState.initRobot(ORANGE);
    //testRobot.setVisitedCheckpoints(tab);
	//bool testBool = testRobot.getVisitedCheckpoints()[0] == 0;
    //vector<unique_ptr<Robot>> & refRobots = testState.players;
    //BOOST_CHECK_EQUAL(testState.getPlayers(),testState.players);
    //bool testBool = testState.getPlayers()[0]==0;
    //*(testState.getPlayers()[0]).getColor();
    //BOOST_CHECK(testBool);

    //testState.setEndGame(1);
    //BOOST_CHECK_EQUAL(testState.getEndGame(),1);

    testState.setEndRound(1);
    BOOST_CHECK_EQUAL(testState.getEndRound(),1);

    testState.setActionInRound(12);
    BOOST_CHECK_EQUAL(testState.getActionInRound(),12);
    
    //testState.initMap("../res/map.txt");
    //BOOST_CHECK_EQUAL(testState.initMap("../res/map.txt"),1);
}
