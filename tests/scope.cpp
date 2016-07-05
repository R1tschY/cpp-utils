#include <stdexcept>
#include <boost/test/unit_test.hpp>

#include <cpp-utils/scope.h>

BOOST_AUTO_TEST_SUITE(Scope_Tests)

BOOST_AUTO_TEST_CASE(scope_exit_)
{
  int r = 0;
  {
    scope(exit) { r = 42; };
  }
  BOOST_CHECK_EQUAL(r, 42);
}

BOOST_AUTO_TEST_CASE(scope_fail_)
{
  int r = 0;
  try {
    scope(fail) { r = 42; };
    throw std::runtime_error("fail");
  }
  catch (...) { }
  BOOST_CHECK_EQUAL(r, 42);

  r = 0;
  try {
    scope(fail) { r = 42; };
  }
  catch (...) { }
  BOOST_CHECK_EQUAL(r, 0);
}

BOOST_AUTO_TEST_CASE(scope_success_)
{
  int r = 0;
  try {
    scope(success) { r = 42; };
    throw std::runtime_error("fail");
  }
  catch (...) { }
  BOOST_CHECK_EQUAL(r, 0);

  r = 0;
  try {
    scope(success) { r = 42; };
  }
  catch (...) { }
  BOOST_CHECK_EQUAL(r, 42);
}

BOOST_AUTO_TEST_SUITE_END()
