#include <boost/test/unit_test.hpp>
#include "../../src/shared/state.h"
#include <bits/stdc++.h> 
using namespace std; 

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestConvBelt)
{
	ConvBelt testCV {};
	
	testCV.setConvBeltSpeed(true);
	BOOST_CHECK_EQUAL(testCV.getConvBeltSpeed(), true);
	testCV.setConvBeltTypeId(CB_N_S);
	BOOST_CHECK_EQUAL(testCV.getConvBeltTypeId(), CB_N_S);

	testCV.setConvBeltSpeed(true);
	BOOST_CHECK_EQUAL(testCV.getConvBeltSpeed(), true);
}
