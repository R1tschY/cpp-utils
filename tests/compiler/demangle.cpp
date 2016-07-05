#include <type_traits>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>
#include <iostream>

#include <cpp-utils/compiler/demangle.h>

namespace TestMe {

template<typename T>
struct A { virtual ~A() = default; };

} // namespace TestMe

BOOST_AUTO_TEST_SUITE(Demangle_Tests)

BOOST_AUTO_TEST_CASE(type_info)
{
  BOOST_CHECK_EQUAL(cpp::demangle(typeid(TestMe::A<int>).name()), "TestMe::A<int>");
  BOOST_CHECK_EQUAL(cpp::demangle_or_throw(typeid(TestMe::A<int>).name()), "TestMe::A<int>");
}

BOOST_AUTO_TEST_CASE(invalid_argument)
{
  BOOST_CHECK_EQUAL(cpp::demangle("std::size_t"), "");
  BOOST_CHECK_THROW(cpp::demangle_or_throw("std::size_t"), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
