#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include <bits/stdc++.h> 
using namespace std; 

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestCheckPoint)
{
    CheckPoint testCP {};
    Robot testRobot {};
    
    testCP.setCheckPointFigure(5);
    BOOST_CHECK_EQUAL(testCP.getCheckPointFigure(), 5);

    BOOST_CHECK_EQUAL(testCP.getCheckPointFigure());
    
    BOOST_CHECK_EQUAL(testCP.isVisited(testRobot),false);
}