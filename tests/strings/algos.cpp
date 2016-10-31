#include <type_traits>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>
#include <iostream>
#include <string>

#include <cpp-utils/strings/algorithm.h>
#include <cpp-utils/strings/string_view.h>

BOOST_AUTO_TEST_SUITE(algorithm_Tests)

// TODO: test against std::string, cpp::string_view, boost::string_ref, QString,
// QStringRef, QLatin1String, gsl::string_span

BOOST_AUTO_TEST_CASE(join_test_cases)
{
  using namespace std::literals;
  using namespace cpp::string_view_literals;

  // common cases
  {
    std::vector<std::string> v = {"a", "bc", "def"};
    std::string s;
    cpp::string::join(", "s, v, s);
    BOOST_CHECK_EQUAL(s, "a, bc, def");
  }

  {
    std::vector<std::string> v = {"a", "bc", "def"};
    std::string s;
    cpp::string::join(cpp::string_view(", "), v, s);
    BOOST_CHECK_EQUAL(s, "a, bc, def");
  }

//  {
//    std::vector<cpp::wstring_view> v = {L"a", L"bc", L"def"};
//    std::wstring s;
//    cpp::string::join(L", "s, v, s);
//    BOOST_CHECK_EQUAL(s, L"a, bc, def");
//  }

  // special cases
  {
    std::vector<cpp::string_view> v;
    std::string s;
    cpp::string::join("/"s, v, s);
    BOOST_CHECK_EQUAL(s, "");
  }

  {
    std::vector<cpp::string_view> v;
    std::string s;
    cpp::string::join(""s, v, s);
    BOOST_CHECK_EQUAL(s, "");
  }

  {
    std::vector<std::string> v = {"a", "bc", "def"};
    std::string s;
    cpp::string::join(""s, v, s);
    BOOST_CHECK_EQUAL(s, "abcdef");
  }
}

BOOST_AUTO_TEST_CASE(lpad_test_cases)
{
  using namespace std::literals;
  using namespace cpp::string_view_literals;

  // common cases
  {
    std::string s = "abc";
    cpp::string::lpad(' ', 6, s);
    BOOST_CHECK_EQUAL(s, "   abc");
    BOOST_CHECK_EQUAL(cpp::string::lpad(' ', 6, std::string("abc")), "   abc");
  }

  // special cases
  {
    std::string s = "abc";
    cpp::string::lpad(' ', 0, s);
    BOOST_CHECK_EQUAL(s, "abc");
    BOOST_CHECK_EQUAL(cpp::string::lpad(' ', 0, std::string("abc")), "abc");
  }

  {
    std::string s = "abc";
    cpp::string::lpad(' ', 1, s);
    BOOST_CHECK_EQUAL(s, "abc");
    BOOST_CHECK_EQUAL(cpp::string::lpad(' ', 1, std::string("abc")), "abc");
  }

  {
    std::string s = "";
    cpp::string::lpad(' ', 6, s);
    BOOST_CHECK_EQUAL(s, "      ");
    BOOST_CHECK_EQUAL(cpp::string::lpad(' ', 6, std::string()), "      ");
  }
}

BOOST_AUTO_TEST_CASE(rpad_test_cases)
{
  using namespace std::literals;
  using namespace cpp::string_view_literals;

  // common cases
  {
    std::string s = "abc";
    cpp::string::rpad(' ', 6, s);
    BOOST_CHECK_EQUAL(s, "abc   ");
    BOOST_CHECK_EQUAL(cpp::string::rpad(' ', 6, std::string("abc")), "abc   ");
  }

  // special cases
  {
    std::string s = "abc";
    cpp::string::rpad(' ', 0, s);
    BOOST_CHECK_EQUAL(s, "abc");
    BOOST_CHECK_EQUAL(cpp::string::rpad(' ', 0, std::string("abc")), "abc");
  }

  {
    std::string s = "abc";
    cpp::string::rpad(' ', 1, s);
    BOOST_CHECK_EQUAL(s, "abc");
    BOOST_CHECK_EQUAL(cpp::string::rpad(' ', 1, std::string("abc")), "abc");
  }

  {
    std::string s = "";
    cpp::string::rpad(' ', 6, s);
    BOOST_CHECK_EQUAL(s, "      ");
    BOOST_CHECK_EQUAL(cpp::string::rpad(' ', 6, std::string()), "      ");
  }
}

BOOST_AUTO_TEST_CASE(ltrim_test_cases)
{
  using namespace std::literals;
  using namespace cpp::string_view_literals;

  // common cases
  {
    std::string s = "   abc   ";
    cpp::string::ltrim(s);
    BOOST_CHECK_EQUAL(s, "abc   ");
    BOOST_CHECK_EQUAL(cpp::string::ltrim(std::string("   abc   ")), "abc   ");
  }

  // special cases
  {
    std::string s = "   ";
    cpp::string::ltrim(s);
    BOOST_CHECK_EQUAL(s, "");
    BOOST_CHECK_EQUAL(cpp::string::ltrim(std::string("   ")), "");
  }

  {
    std::string s = "";
    cpp::string::ltrim(s);
    BOOST_CHECK_EQUAL(s, "");
    BOOST_CHECK_EQUAL(cpp::string::ltrim(std::string()), "");
  }
}

BOOST_AUTO_TEST_CASE(rtrim_test_cases)
{
  using namespace std::literals;
  using namespace cpp::string_view_literals;

  // common cases
  {
    std::string s = "   abc   ";
    cpp::string::rtrim(s);
    BOOST_CHECK_EQUAL(s, "   abc");
    BOOST_CHECK_EQUAL(cpp::string::rtrim(std::string("   abc   ")), "   abc");
  }

  // special cases
  {
    std::string s = "   ";
    cpp::string::rtrim(s);
    BOOST_CHECK_EQUAL(s, "");
    BOOST_CHECK_EQUAL(cpp::string::rtrim(std::string("   ")), "");
  }

  {
    std::string s = "";
    cpp::string::rtrim(s);
    BOOST_CHECK_EQUAL(s, "");
    BOOST_CHECK_EQUAL(cpp::string::rtrim(std::string()), "");
  }
}

// TODO: fix tests
//BOOST_AUTO_TEST_CASE(has_prefix_test_cases)
//{
//  // common cases
//  BOOST_CHECK_EQUAL(true, cpp::string::has_prefix("fix", "fixABC"));
//  BOOST_CHECK_EQUAL(false, cpp::string::has_prefix("fix", "ABCfix"));
//  BOOST_CHECK_EQUAL(false, cpp::string::has_prefix("fix", ""));
//  BOOST_CHECK_EQUAL(false, cpp::string::has_prefix("fix", "f"));
//}
//
//BOOST_AUTO_TEST_CASE(has_suffix_test_cases)
//{
//  // common cases
//  BOOST_CHECK_EQUAL(false, cpp::string::has_suffix("fix", "fixABC"));
//  BOOST_CHECK_EQUAL(true, cpp::string::has_suffix("fix", "ABCfix"));
//  BOOST_CHECK_EQUAL(false, cpp::string::has_suffix("fix", ""));
//  BOOST_CHECK_EQUAL(false, cpp::string::has_suffix("fix", "f"));
//}
//
//BOOST_AUTO_TEST_CASE(ensure_prefix_test_cases)
//{
//  using namespace std::literals;
//  using namespace cpp::string_view_literals;
//
//  // common cases
//  {
//    std::string s = "ABC";
//    cpp::string::ensure_prefix("fix", s);
//    BOOST_CHECK_EQUAL(s, "fixABC");
//  }
//  {
//    std::string s = "fixABC";
//    cpp::string::ensure_prefix("fix", s);
//    BOOST_CHECK_EQUAL(s, "fixABC");
//  }
//
//  // special cases
//  {
//    std::string s = "fix";
//    cpp::string::ensure_prefix("fix", s);
//    BOOST_CHECK_EQUAL(s, "fix");
//  }
//  {
//    std::string s = "";
//    cpp::string::ensure_prefix("fix", s);
//    BOOST_CHECK_EQUAL(s, "fix");
//  }
//  {
//    std::string s = "f";
//    cpp::string::ensure_prefix("fix", s);
//    BOOST_CHECK_EQUAL(s, "fixf");
//  }
//}
//
//BOOST_AUTO_TEST_CASE(ensure_suffix_test_cases)
//{
//  using namespace std::literals;
//  using namespace cpp::string_view_literals;
//
//  // common cases
//  {
//    std::string s = "ABC";
//    cpp::string::ensure_suffix("fix", s);
//    BOOST_CHECK_EQUAL(s, "ABCfix");
//  }
//  {
//    std::string s = "ABCfix";
//    cpp::string::ensure_suffix("fix", s);
//    BOOST_CHECK_EQUAL(s, "ABCfix");
//  }
//
//  // special cases
//  {
//    std::string s = "fix";
//    cpp::string::ensure_suffix("fix", s);
//    BOOST_CHECK_EQUAL(s, "fix");
//  }
//  {
//    std::string s = "";
//    cpp::string::ensure_suffix("fix", s);
//    BOOST_CHECK_EQUAL(s, "fix");
//  }
//  {
//    std::string s = "f";
//    cpp::string::ensure_suffix("fix", s);
//    BOOST_CHECK_EQUAL(s, "ffix");
//  }
//}
//
//BOOST_AUTO_TEST_CASE(remove_prefix_test_cases)
//{
//  using namespace std::literals;
//  using namespace cpp::string_view_literals;
//
//  // common cases
//  {
//    std::string s = "ABCfix";
//    cpp::string::remove_prefix("fix", s);
//    BOOST_CHECK_EQUAL(s, "ABCfix");
//  }
//  {
//    std::string s = "fixABC";
//    cpp::string::remove_prefix("fix", s);
//    BOOST_CHECK_EQUAL(s, "ABC");
//  }
//
//  // special cases
//  {
//    std::string s = "fix";
//    cpp::string::remove_prefix("fix", s);
//    BOOST_CHECK_EQUAL(s, "");
//  }
//  {
//    std::string s = "";
//    cpp::string::remove_prefix("fix", s);
//    BOOST_CHECK_EQUAL(s, "");
//  }
//  {
//    std::string s = "f";
//    cpp::string::remove_prefix("fix", s);
//    BOOST_CHECK_EQUAL(s, "f");
//  }
//}
//
//BOOST_AUTO_TEST_CASE(remove_suffix_test_cases)
//{
//  using namespace std::literals;
//  using namespace cpp::string_view_literals;
//
//  // common cases
//  {
//    std::string s = "ABCfix";
//    cpp::string::remove_suffix("fix", s);
//    BOOST_CHECK_EQUAL(s, "ABC");
//  }
//  {
//    std::string s = "fixABC";
//    cpp::string::remove_suffix("fix", s);
//    BOOST_CHECK_EQUAL(s, "fixABC");
//  }
//
//  // special cases
//  {
//    std::string s = "fix";
//    cpp::string::remove_suffix("fix", s);
//    BOOST_CHECK_EQUAL(s, "");
//  }
//  {
//    std::string s = "";
//    cpp::string::remove_suffix("fix", s);
//    BOOST_CHECK_EQUAL(s, "");
//  }
//  {
//    std::string s = "f";
//    cpp::string::remove_suffix("fix", s);
//    BOOST_CHECK_EQUAL(s, "f");
//  }
//}

BOOST_AUTO_TEST_SUITE_END()
