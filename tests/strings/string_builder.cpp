#include <type_traits>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <cpp-utils/strings/string_builder.h>

BOOST_AUTO_TEST_SUITE(StringBuilder_Tests)

BOOST_AUTO_TEST_CASE(common_use_cases)
{
  using namespace std::literals;
  using namespace cpp::string_view_literals;

  {
    std::string s = cpp::concatenate<std::string>("a"s, "b"s, "c"s);
    BOOST_CHECK_EQUAL(s, "abc");
  }

#ifndef __clang__
  {
    std::string s = cpp::concatenate<std::string>("a"sv, "b"sv, "c"s);
    BOOST_CHECK_EQUAL(s, "abc");
  }

  {
    std::string s = cpp::concatenate<std::string>("a"sv, 'b', "c");
    BOOST_CHECK_EQUAL(s, "abc");
  }

  {
    std::string s = cpp::concatenate<std::string>("abc"sv, 'd', "efg", "hij"s);
    BOOST_CHECK_EQUAL(s, "abcdefghij");
  }
#endif

  {
    std::string s;
    cpp::concatenate_to(s, "a"s, "b"s, "c"s);
    BOOST_CHECK_EQUAL(s, "abc");
  }

  {
    std::string s = cpp::concatenate_to(std::string(), "a"s, "b"s, "c"s);
    BOOST_CHECK_EQUAL(s, "abc");
  }

//  {
//    std::string s = cpp::string_builder<std::string>() << "a"s + "b"s + "c"s;
//    BOOST_CHECK_EQUAL(s, "abc");
//  }
//
//  {
//    std::string s;
//    cpp::string_builder(s) << "a"s + "b"s + "c"s;
//    BOOST_CHECK_EQUAL(s, "abc");
//  }
}

//typedef boost::mpl::list<A, std::unique_ptr<A>> test_types;
//BOOST_AUTO_TEST_CASE_TEMPLATE(use_copy_policy_of, T, test_types)
//{
//  struct test : cpp::use_copy_policy_of<T> { };
//
//  BOOST_CHECK_EQUAL(std::is_copy_constructible<test>::value, std::is_copy_constructible<T>::value);
//  BOOST_CHECK_EQUAL(std::is_copy_assignable<test>::value, std::is_copy_assignable<T>::value);
//  BOOST_CHECK_EQUAL(std::is_move_constructible<test>::value, std::is_move_constructible<T>::value);
//  BOOST_CHECK_EQUAL(std::is_move_assignable<test>::value, std::is_move_assignable<T>::value);
//}

BOOST_AUTO_TEST_SUITE_END()
