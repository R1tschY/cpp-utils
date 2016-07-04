#include <type_traits>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <cpp-utils/compiler/demangle.h>

namespace TestMe {

struct A { virtual ~A() = default; };

} // namespace TestMe

BOOST_AUTO_TEST_SUITE(Demangle_Tests)

BOOST_AUTO_TEST_CASE(type_info)
{
  BOOST_CHECK_EQUAL(cpp::demangle(typeid(TestMe::A).name()), "TestMe::A");
}

BOOST_AUTO_TEST_CASE(exception)
{
  BOOST_CHECK_EQUAL(cpp::demangle(std::bad_exception().what()), "std::bad_exception");
}

BOOST_AUTO_TEST_SUITE_END()
