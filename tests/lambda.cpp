#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

#include <cpp-utils/lambda.h>
#include <cpp-utils/algorithm/container.h>

using namespace cpp::lambda;

#define BOOST_CHECK_EQUAL_RANGES(a, b) \
  BOOST_CHECK_EQUAL_COLLECTIONS( \
    std::begin(a), std::end(a), std::begin(b), std::end(b) \
  )

BOOST_AUTO_TEST_SUITE(LambdaTests)

BOOST_AUTO_TEST_CASE(param)
{
  BOOST_CHECK_EQUAL( 1, _a(1, 45, 67));
  BOOST_CHECK_EQUAL(45, _b(1, 45, 67));
}

BOOST_AUTO_TEST_CASE(use_case_add)
{
  auto data = {1, 2, 3, 4, 5};

  BOOST_CHECK_EQUAL(15, cpp::accumulate(data, 0, _add(_a, _b)));
}


BOOST_AUTO_TEST_CASE(use_case_less)
{
  std::vector<int> data = {1, 2, 3, 4, 5};

  cpp::sort(data, _less(_a, _b));
  BOOST_CHECK(cpp::is_sorted(data));
}

//BOOST_AUTO_TEST_CASE(use_case_var)
//{
//  std::vector<int> data = {1, 2, 3, 4, 5};
//  std::vector<int> out;
//
//  cpp::transform(data, out, _iadd(_var(0), _a));
//
//  std::vector<int> expected{1, 3, 6, 10, 15};
//  BOOST_CHECK_EQUAL_RANGES(expected, out);
//}

BOOST_AUTO_TEST_CASE(use_case_varref)
{
  std::vector<int> data = {1, 2, 3, 4, 5};

  int i = 0;
  cpp::for_each(data, _iadd(_varref(i), _a));

  BOOST_CHECK_EQUAL(15, i);
}

BOOST_AUTO_TEST_CASE(use_case_field)
{
  struct X { int value; };

  std::vector<X> data{X{1}, X{2}, X{3}, X{4}, X{5}};

  cpp::sort(data, _less(_FIELD(&X::value, _a), _FIELD(&X::value, _b)));

  BOOST_CHECK(cpp::is_sorted(
    data, _less(_FIELD(&X::value, _a), _FIELD(&X::value, _b))
  ));
}

BOOST_AUTO_TEST_SUITE_END()

