#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/ConvBelt.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(testConvBelt)
{
	ConvBelt testCV {};
	
	testCV.setConvBeltSpeed(true);
	BOOST_CHECK_EQUAL(testCV.getConvBeltSpeed(), true);
	//testCV.setConvBeltId(CB_N_S);
	//BOOST_CHECK_EQUAL(testCV.getConvBeltId(), CB_N_S);
}
