#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"

using namespace std; 

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestElement)
{
    Element testElement;

    testElement.setTypeId(BONUS);
	BOOST_CHECK_EQUAL((testElement.getTypeId()), BONUS);

}