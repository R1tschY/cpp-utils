#include <boost/test/unit_test.hpp>

#include <cpp-utils/down_cast.h>

namespace {

struct A { virtual ~A() { } };
struct B : A { };
struct C : A { };

} // namespace

BOOST_AUTO_TEST_SUITE(DownCast_Tests)

BOOST_AUTO_TEST_CASE(pointer)
{
  B b;
  A* ab = &b;
  BOOST_CHECK(&b == cpp::down_cast<B>(ab));

#ifndef NDEBUG
  // failure
  C c;
  A* ac = &c;
  BOOST_CHECK_THROW(cpp::down_cast<B>(ac), cpp::assert_failure);
#endif
}

BOOST_AUTO_TEST_CASE(ref)
{
  B b;
  A& ab = b;
  BOOST_CHECK(&b == &cpp::down_cast<B>(ab));

#ifndef NDEBUG
  // failure
  C c;
  A& ac = c;
  BOOST_CHECK_THROW(cpp::down_cast<B>(ac), cpp::assert_failure);
#endif
}

BOOST_AUTO_TEST_SUITE_END()
