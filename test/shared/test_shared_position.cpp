#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestPosition)
{
  Element testEntity {};
  Position testEntityPos= testEntity.getPosition();
  testEntityPos.setX(5);
  BOOST_CHECK_EQUAL(testEntityPos.getX(),5);
  testEntityPos.setY(51);
  BOOST_CHECK_EQUAL(testEntityPos.getY(),51);
}
