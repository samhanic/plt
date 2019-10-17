#include <boost/test/unit_test.hpp>
#include "../../src/shared/state/Bonus.h"

using namespace ::state;

BOOST_AUTO_TEST_CASE(TestBonus)
{
	Bonus bn {};
	bn.setBonusTypeId(BONUS_HEAL);
	BOOST_CHECK_EQUAL((bn.getBonusTypeId()),BONUS_HEAL);
	
	bn.setBonusAvailability(0);
	BOOST_CHECK_EQUAL((bn.getBonusAvailability(true)),0);
}
