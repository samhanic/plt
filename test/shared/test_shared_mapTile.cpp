#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/MapTile.h"

using namespace state;

BOOST_AUTO_TEST_CASE(TestTile)
{
	MapTile testTile {};
	
	TypeId = ROBOT;
	
	BOOST_CHECK_EQUAL(testTile.dropBomb,1);
	BOOST_CHECK_EQUAL(testTile.removeBomb,1);
}
