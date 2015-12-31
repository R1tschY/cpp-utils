#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#include <memory>
#include <type_traits>
#include <cpp-utils/memory/not_null.h>
#include <cpp-utils/assert.h>
#include <cpp-utils/printing.h>

struct KnownType { void func() { } };

BOOST_AUTO_TEST_SUITE(Memory_Not_Null_Tests)


typedef boost::mpl::list<KnownType*,std::unique_ptr<KnownType>> test_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(type_correctness, T, test_types)
{
  using not_null = cpp::not_null<T>;

  BOOST_CHECK_EQUAL(std::is_copy_constructible<T>::value, std::is_copy_constructible<not_null>::value);
  BOOST_CHECK_EQUAL(std::is_move_constructible<T>::value, std::is_move_constructible<not_null>::value);
  BOOST_CHECK_EQUAL(std::is_copy_assignable<T>::value, std::is_copy_assignable<not_null>::value);
  BOOST_CHECK_EQUAL(std::is_move_assignable<T>::value, std::is_move_assignable<not_null>::value);

  BOOST_CHECK_EQUAL(std::is_move_assignable<T>::value, std::is_move_assignable<not_null>::value);

  BOOST_CHECK_EQUAL(true, (std::is_constructible<not_null, T&&>::value));
  BOOST_CHECK_EQUAL(true, (std::is_assignable<not_null, T&&>::value));
}

BOOST_AUTO_TEST_CASE(ptr_support)
{
  using not_null_ptr_t = cpp::not_null<KnownType*>;
  KnownType* null_ptr = nullptr;

  std::unique_ptr<KnownType> not_null_owner(new KnownType());
  KnownType* not_null_ptr = not_null_owner.get();

  // constructor
  {
    BOOST_CHECK_THROW(not_null_ptr_t test(null_ptr), cpp::assert_failure);
    BOOST_CHECK_EQUAL(not_null_ptr, not_null_ptr_t(not_null_ptr));
  }

  // assignment
  {
    not_null_ptr_t t(not_null_ptr);

    BOOST_CHECK(t != nullptr);

    BOOST_CHECK_THROW(t = null_ptr, cpp::assert_failure);
    BOOST_CHECK_NO_THROW(t = not_null_ptr);

    BOOST_CHECK(t != nullptr);
  }

  // copy
  {
    not_null_ptr_t t(not_null_ptr);
    not_null_ptr_t u(not_null_ptr);

    BOOST_CHECK_NO_THROW(t = u);
  }

  // move
  {
    not_null_ptr_t t(not_null_ptr);
    not_null_ptr_t u(not_null_ptr);

    BOOST_CHECK_NO_THROW(t = std::move(u));
  }

  // compare
  {
    not_null_ptr_t t(not_null_ptr);
    not_null_ptr_t u(not_null_ptr);

    BOOST_CHECK(t);
    BOOST_CHECK(!!t);
    BOOST_CHECK(t != nullptr);
    BOOST_CHECK(!(t == nullptr));
    BOOST_CHECK(nullptr != t);
    BOOST_CHECK(!(nullptr == t));
    BOOST_CHECK(t == not_null_ptr);
    BOOST_CHECK(!(t != not_null_ptr));
    BOOST_CHECK(not_null_ptr == t);
    BOOST_CHECK(!(not_null_ptr != t));
    BOOST_CHECK(t == u);
    BOOST_CHECK(!(t != u));
  }

  // usage
  {
    not_null_ptr_t t(not_null_ptr);

    BOOST_CHECK_NO_THROW({
      t->func();
      (*t).func();
      t.get()->func();
    });
  }
}

BOOST_AUTO_TEST_CASE(unique_ptr_support)
{
  using not_null_unique_ptr = cpp::not_null<std::unique_ptr<KnownType>>;
  KnownType* null_ptr = nullptr;

  // constructor
  {
    BOOST_CHECK_THROW(not_null_unique_ptr t(null_ptr), cpp::assert_failure);
    BOOST_CHECK_THROW(not_null_unique_ptr t(std::unique_ptr<KnownType>(nullptr)), cpp::assert_failure);

    BOOST_CHECK_NO_THROW(not_null_unique_ptr t(new KnownType()));
    BOOST_CHECK_NO_THROW(not_null_unique_ptr t(std::unique_ptr<KnownType>(new KnownType())));
  }

  // assignment
  {
    not_null_unique_ptr t(new KnownType());

    BOOST_CHECK(t != nullptr);

    BOOST_CHECK_THROW(t = null_ptr, cpp::assert_failure);
    BOOST_CHECK_THROW(t = std::unique_ptr<KnownType>(nullptr), cpp::assert_failure);

    BOOST_CHECK_NO_THROW(t = new KnownType());
    BOOST_CHECK_NO_THROW(t = std::unique_ptr<KnownType>(new KnownType()));

    BOOST_CHECK(t != nullptr);
  }

  // move
  {
    not_null_unique_ptr t(new KnownType());
    not_null_unique_ptr u(new KnownType());

    BOOST_CHECK_NO_THROW(t = std::move(u));

    BOOST_CHECK(t != nullptr);
  }

  // usage
  {
    BOOST_CHECK_NO_THROW({
      not_null_unique_ptr t(new KnownType());
      t->func();
      (*t).func();
      t.get()->func();
    });
  }
}

BOOST_AUTO_TEST_SUITE_END()





