#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace std; 

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestRotator)
{
	Rotator testRotator;
	
	testRotator.setRotatorTypeId(ROT_CLK);
	BOOST_CHECK_EQUAL((testRotator.getRotatorTypeId()), ROT_CLK);
}
