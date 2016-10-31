#include <type_traits>
#include <utility>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <cpp-utils/printf_builder.h>
#include <cpp-utils/strings/string_literal.h>

namespace {

template<typename T>
cpp::type_t<std::decay_t<T>> get_type(T&& t)
{
  return cpp::type_t<std::decay_t<T>>();
}

} // namespace

BOOST_AUTO_TEST_SUITE(PrintfBuilder_Tests)

BOOST_AUTO_TEST_CASE(std_support)
{
  BOOST_CHECK_EQUAL("abc", cpp::fmtstr(get_type(lit("abc"))).data);
  BOOST_CHECK_EQUAL("%s", cpp::fmtstr(get_type("a")).data);
  BOOST_CHECK_EQUAL("%d", cpp::fmtstr(get_type(1234)).data);
  BOOST_CHECK_EQUAL("%u", cpp::fmtstr(get_type(1234U)).data);
  BOOST_CHECK_EQUAL("%lu", cpp::fmtstr(get_type(1234UL)).data);
  BOOST_CHECK_EQUAL("%llu", cpp::fmtstr(get_type(1234ULL)).data);
  BOOST_CHECK_EQUAL("%hd", cpp::fmtstr(get_type(short(1234))).data);
  BOOST_CHECK_EQUAL("%c", cpp::fmtstr(get_type(char(1234))).data);
  BOOST_CHECK_EQUAL("%hhd", cpp::fmtstr(get_type(static_cast<signed char>(1234))).data);
}

BOOST_AUTO_TEST_CASE(common_use_cases)
{
  // printf
  BOOST_CHECK_EQUAL(5, cpp::printf(lit("abc "), 3));

  // sprintf
  {
    char buffer[32];
    BOOST_CHECK_EQUAL(5, cpp::sprintf(buffer, lit("abc "), 3));
    BOOST_CHECK_EQUAL("abc 3", buffer);
  }
  {
    char buffer[32];
    cpp::sprintf(buffer, 1L, ", ", 3.14f, ", ", 42.0, " / ", 67ULL, lit("\n"));
    BOOST_CHECK_EQUAL("1, 3.140000, 42.000000 / 67\n", buffer);
  }
  {
    char test[] = "test ";
    char buffer[32];
    cpp::sprintf(buffer, lit("lit "), test, "test");
    BOOST_CHECK_EQUAL("lit test test", buffer);
  }
  {
    char buffer[32];

    int* ptr = reinterpret_cast<int*>(0x42);
    cpp::sprintf(buffer, ptr);
    BOOST_CHECK_EQUAL("0x42", buffer);
  }
}

BOOST_AUTO_TEST_SUITE_END()
