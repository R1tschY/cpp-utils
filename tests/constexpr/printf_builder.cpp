#include <type_traits>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <cpp-utils/constexpr/printf_builder.h>

template<char...Chars>
constexpr
std::integer_sequence<char, Chars...> operator "" _lit()
{
  return std::integer_sequence<char, Chars...>{};
}

template<typename Str, std::size_t...I>
auto build_string(std::index_sequence<I...>) {
  return std::integer_sequence<char, Str().chars[I]...>();
}

#define lit(str) []{\
  struct Str { const char * chars = str; };\
  return build_string<Str>(std::make_index_sequence<strlen(str)>());\
}()

BOOST_AUTO_TEST_SUITE(PrintfBuilder_Tests)

BOOST_AUTO_TEST_CASE(common_use_cases)
{
  {
    constexpr auto a1 = cpp::fmtstr("a\0");
    BOOST_CHECK_EQUAL("a", a1.data);

    constexpr auto a2 = cpp::make_constexpr_array("a");
    BOOST_CHECK_EQUAL("a", a2.data);

    BOOST_CHECK_EQUAL(4, cpp::printf(lit("abc"), 3));
  }
}

BOOST_AUTO_TEST_SUITE_END()
