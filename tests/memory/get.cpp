#include <boost/test/unit_test.hpp>

#include <memory>

#include <cpp-utils/memory/get.h>

BOOST_AUTO_TEST_SUITE(Memory_Get_Tests)

BOOST_AUTO_TEST_CASE(Memory_get_unique_ptr)
{
  struct T { };
  std::unique_ptr<T> t;
  BOOST_CHECK_EQUAL(true, (std::is_same<decltype(cpp::get(t)), T*>::value));
}

BOOST_AUTO_TEST_CASE(Memory_get_pointer)
{
  struct T { };
  T* t = nullptr;
  //BOOST_CHECK_EQUAL(nullptr, cpp::get(t));
}

BOOST_AUTO_TEST_CASE(Memory_get_int)
{
  int i = 42;
  //BOOST_CHECK_EQUAL(42, cpp::get(i));
}

BOOST_AUTO_TEST_SUITE_END()
