#include <algorithm>
#include <boost/test/unit_test.hpp>

#include <cpp-utils/iterator_range.h>

using namespace cpp;

BOOST_AUTO_TEST_SUITE(IteratorRange_Tests)

BOOST_AUTO_TEST_CASE(iterator_range_tests)
{
  std::vector<int> data = { 1, 2, 3, 4 };
  using Iter = std::vector<int>::iterator;

  // STL algo
  {
    auto test = iterator_range<Iter, Iter>(data.begin(), data.end());
    BOOST_CHECK_EQUAL(10, std::accumulate(test.begin(), test.end(), 0));
  }

  // c++11 for
  {
    auto test = iterator_range<Iter, Iter>(data.begin(), data.end());

    int result = 0;
    for (auto i : test)
      result += i;

    BOOST_CHECK_EQUAL(10, result);
  }
}

BOOST_AUTO_TEST_CASE(make_range_tests)
{
  std::vector<int> data = { 1, 2, 3, 4 };

  // two iterators
  {
    auto test = make_range(data.begin(), data.end());
    int result = 0; for (auto i : test) result += i;
    BOOST_CHECK_EQUAL(10, result);
  }

  auto ref = make_range(data.begin(), data.end());

  // std::pair support
  {
    auto test = make_range(std::make_pair(data.begin(), data.end()));
    BOOST_CHECK(test == ref);

    int result = 0; for (auto i : test) result += i;
    BOOST_CHECK_EQUAL(10, result);
  }

  // range support
  {
    auto test = make_range(data);
    BOOST_CHECK(test == ref);

    int result = 0;
    for (auto i : test)
      result += i;
    BOOST_CHECK_EQUAL(10, result);
  }
}

BOOST_AUTO_TEST_SUITE_END()
