#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include <bits/stdc++.h> 
using namespace std; 

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestMapTile)
{
    MapTile mt {};

    mt.setBombDropped(true);
    BOOST_CHECK_EQUAL((mt.getBombDropped()),true);

    
    mt.setIdStatic(NO_ID);
    BOOST_CHECK_EQUAL((mt.getIdStatic()),NO_ID);
}
