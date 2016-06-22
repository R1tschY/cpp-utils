/*
 *      Copyright 2015 R1tschY <r1tschy@yahoo.de>
 *      
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef CPP_UTILS_MEMORY_NOT_NULL_H_
#define CPP_UTILS_MEMORY_NOT_NULL_H_

template<typename T>
class not_null;

#include <cstddef>
#include <utility>
#include <iosfwd>
#include "../assert.h"
#include "../compiler/attributes.h"
#include "maybe_null.h"

namespace cpp {

template<typename T>
class not_null
{
public:
  not_null(std::nullptr_t) = delete;

  template<typename...Args>
  not_null(Args&&...args) cpp_attribute_nonnull(1)
  : ptr_(std::forward<Args>(args)...)
  {
    cpp_assert(ptr_ != nullptr);
  }

  not_null(const maybe_null<T>& t)
  : ptr_(t.get_wrapped())
  {
    cpp_assert(ptr_ != nullptr);
  }

  not_null(maybe_null<T>&& t)
  : ptr_(std::move(t.get_wrapped()))
  {
    cpp_assert(ptr_ != nullptr);
  }

  auto get() cpp_attribute_returns_nonnull { return &(*ptr_); }
  T& get_inner() noexcept { return ptr_; }
  const T& get_inner() const noexcept { return ptr_; }
  auto operator*() noexcept { return *ptr_; }
  auto operator*() const noexcept { return *ptr_; }
  auto operator->() cpp_attribute_returns_nonnull { return &(*ptr_); }
  auto operator->() cpp_attribute_returns_nonnull const { return &(*ptr_); }

  bool operator==(std::nullptr_t) const noexcept
  {
    return false;
  }

  bool operator!=(std::nullptr_t) const noexcept
  {
    return true;
  }

  bool operator==(const T& rhs) const
  {
    return ptr_ == rhs;
  }

  bool operator!=(const T& rhs) const
  {
    return ptr_ != rhs;
  }

  bool operator==(const not_null& rhs) const
  {
    return ptr_ == rhs.ptr_;
  }

  bool operator!=(const not_null& rhs) const
  {
    return ptr_ != rhs.ptr_;
  }

  explicit operator bool() const noexcept
  {
    return true;
  }

  template<class C, class Tr>
  friend std::basic_ostream<C, Tr>& operator<<(std::basic_ostream<C, Tr>& out, const not_null& t)
  {
    return out << t.ptr_;
  }

private:
  T ptr_;
};

template<typename T>
bool operator==(const T& lhs, const not_null<T>& rhs)
{
  return rhs == lhs;
}

template<typename T>
bool operator!=(const T& lhs, const not_null<T>& rhs)
{
  return rhs != lhs;
}

template<typename T>
bool operator==(std::nullptr_t, const not_null<T>&) noexcept
{
  return false;
}

template<typename T>
bool operator!=(std::nullptr_t, const not_null<T>&) noexcept
{
  return true;
}

} // namespace cpp

#endif /* CPP_UTILS_MEMORY_NOT_NULL_H_ */
