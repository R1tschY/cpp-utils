#include <type_traits>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <cpp-utils/memory/unique_array.h>

BOOST_AUTO_TEST_SUITE(UniqueArray_Tests)

BOOST_AUTO_TEST_CASE(common_use_cases)
{
  {
    auto test = cpp::make_unique_array<int>(5);

    BOOST_CHECK_NE(test.data(), static_cast<void*>(0));
    BOOST_CHECK_EQUAL(test.size(), 5);

    test.reset();

    BOOST_CHECK_EQUAL(test.data(), static_cast<void*>(0));
    BOOST_CHECK_EQUAL(test.size(), 0);
  }
}

BOOST_AUTO_TEST_CASE(reset_tests)
{
  {
    int deleter_count = 0;

    struct test_deleter
    {
      void operator()(int* ptr)
      {
        delete[] ptr;
        ++deleter_count;
      }
    };

    auto test = cpp::unique_array<int, test_deleter>(new int[5], 5);

    BOOST_CHECK_NE(test.data(), static_cast<void*>(0));
    BOOST_CHECK_EQUAL(test.size(), 5);
    BOOST_CHECK_EQUAL(deleter_count, 0);

    test.reset();

    BOOST_CHECK_EQUAL(test.data(), static_cast<void*>(0));
    BOOST_CHECK_EQUAL(test.size(), 0);
    BOOST_CHECK_EQUAL(deleter_count, 1);
  }
}

BOOST_AUTO_TEST_SUITE_END()
