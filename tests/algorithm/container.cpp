#include <algorithm>
#include <boost/test/unit_test.hpp>

#include "../../include/cpp-utils/algorithm/container.h"

using namespace cpp;

BOOST_AUTO_TEST_SUITE(RangeStl_Tests)

BOOST_AUTO_TEST_CASE(reserve_tests)
{
  // std::vector
  {
    std::vector<int> test;
    cpp::reserve(test, 12);
    BOOST_CHECK_GE(12, test.capacity());
  }

  // std::list
  {
    std::list<int> test;
    cpp::reserve(test, 12); // check if compiles
  }
}

BOOST_AUTO_TEST_SUITE_END()
