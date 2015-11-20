#include "google/gtest/gtest.h"

#include <memory>
#include <cpp-utils/memory/get.h>

TEST(Memory_get, unique_ptr)
{
  struct T { };
  std::unique_ptr<T> t;
  EXPECT_EQ(true, (std::is_same<decltype(cpp::get(t)), T*>::value));
}

TEST(Memory_get, pointer)
{
  struct T { };
  T* t = nullptr;
  EXPECT_EQ(nullptr, cpp::get(t));
}

TEST(Memory_get, int_)
{
  int i = 42;
  EXPECT_EQ(42, cpp::get(i));
}
