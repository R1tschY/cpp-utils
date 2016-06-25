#include <type_traits>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <cpp-utils/copy_policy.h>

namespace {

struct A { };

} // namespace

BOOST_AUTO_TEST_SUITE(CopyPolicy_Tests)

BOOST_AUTO_TEST_CASE(copy_policy_base)
{
  {
    struct test : cpp::copy_ctor_policy_base<false, false> { };

    BOOST_CHECK(!std::is_copy_constructible<test>::value);
    BOOST_CHECK(std::is_copy_assignable<test>::value);
    BOOST_CHECK(!std::is_move_constructible<test>::value);
    BOOST_CHECK(std::is_move_assignable<test>::value);
  }

  {
    struct test : cpp::copy_assign_policy_base<false, false> { };

    BOOST_CHECK(std::is_copy_constructible<test>::value);
    BOOST_CHECK(!std::is_copy_assignable<test>::value);
    BOOST_CHECK(std::is_move_constructible<test>::value);
    BOOST_CHECK(!std::is_move_assignable<test>::value);
  }

  {
    struct test : cpp::copy_ctor_policy_base<false, true> { };

    BOOST_CHECK(!std::is_copy_constructible<test>::value);
    BOOST_CHECK(std::is_copy_assignable<test>::value);
    BOOST_CHECK(std::is_move_constructible<test>::value);
    BOOST_CHECK(std::is_move_assignable<test>::value);
  }

  {
    struct test : cpp::copy_assign_policy_base<false, true> { };

    BOOST_CHECK(std::is_copy_constructible<test>::value);
    BOOST_CHECK(!std::is_copy_assignable<test>::value);
    BOOST_CHECK(std::is_move_constructible<test>::value);
    BOOST_CHECK(std::is_move_assignable<test>::value);
  }

  {
    struct test : cpp::copy_ctor_policy_base  <true, false>
                , cpp::copy_assign_policy_base<false, true>
    { };

    BOOST_CHECK(std::is_copy_constructible<test>::value);
    BOOST_CHECK(!std::is_copy_assignable<test>::value);
    BOOST_CHECK(std::is_move_assignable<test>::value);
    // if copyable then also movable
  }

  {
    struct test : cpp::copy_ctor_policy_base  <true, false>
                , cpp::copy_assign_policy_base<true, false>
    { };

    BOOST_CHECK(std::is_copy_constructible<test>::value);
    BOOST_CHECK(std::is_copy_assignable<test>::value);
    // if copyable then also movable
  }

  {
    struct test : cpp::copy_ctor_policy_base  <true, true>
                , cpp::copy_assign_policy_base<true, true>
    { };

    BOOST_CHECK(std::is_copy_constructible<test>::value);
    BOOST_CHECK(std::is_copy_assignable<test>::value);
    BOOST_CHECK(std::is_move_constructible<test>::value);
    BOOST_CHECK(std::is_move_assignable<test>::value);
  }
}

typedef boost::mpl::list<A, std::unique_ptr<A>> test_types;
BOOST_AUTO_TEST_CASE_TEMPLATE(use_copy_policy_of, T, test_types)
{
  struct test : cpp::use_copy_policy_of<T> { };

  BOOST_CHECK_EQUAL(std::is_copy_constructible<test>::value, std::is_copy_constructible<T>::value);
  BOOST_CHECK_EQUAL(std::is_copy_assignable<test>::value, std::is_copy_assignable<T>::value);
  BOOST_CHECK_EQUAL(std::is_move_constructible<test>::value, std::is_move_constructible<T>::value);
  BOOST_CHECK_EQUAL(std::is_move_assignable<test>::value, std::is_move_assignable<T>::value);
}

BOOST_AUTO_TEST_CASE(copy_policy_templates)
{
  {
    struct test : cpp::noncopyable { };

    BOOST_CHECK(!std::is_copy_constructible<test>::value);
    BOOST_CHECK(!std::is_copy_assignable<test>::value);
    BOOST_CHECK(!std::is_move_constructible<test>::value);
    BOOST_CHECK(!std::is_move_assignable<test>::value);
  }

  {
    struct test : cpp::movable { };

    BOOST_CHECK(!std::is_copy_constructible<test>::value);
    BOOST_CHECK(!std::is_copy_assignable<test>::value);
    BOOST_CHECK(std::is_move_constructible<test>::value);
    BOOST_CHECK(std::is_move_assignable<test>::value);
  }
}

BOOST_AUTO_TEST_SUITE_END()
