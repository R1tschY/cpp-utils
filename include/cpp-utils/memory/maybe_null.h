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

#ifndef CPP_UTILS_MEMORY_MAYBE_NULL_H_
#define CPP_UTILS_MEMORY_MAYBE_NULL_H_

template<typename T>
class maybe_null;

#include <utility>

#include "../assert.h"
#include "../compiler/attributes.h"
#include "not_null.h"

namespace cpp {

template<typename T>
class maybe_null
{
public:
  maybe_null(T t)
  : t_(t),
    was_checked_(false)
  {
  }

  maybe_null(const not_null<T>& t)
  : t_(t.get_wrapped()),
    was_checked_(true)
  {
  }

  maybe_null(not_null<T>&& t)
  : t_(std::move(t.get_wrapped())),
    was_checked_(true)
  {
  }

  template<typename U>
  maybe_null& operator=(const maybe_null<U>& other)
  {
    t_ = other.t_;
    was_checked_ = other.was_checked_;
    return *this;
  }

  template<typename U>
  maybe_null& operator=(maybe_null<U>&& other)
  {
    t_ = std::move(other.t_);
    was_checked_ = other.was_checked_;
    return *this;
  }

  template<typename U>
  maybe_null& operator=(const not_null<U>& other)
  {
    t_ = other.get_wrapped();
    was_checked_ = true;
    return *this;
  }

  template<typename U>
  maybe_null& operator=(not_null<U>&& other)
  {
    t_ = std::move(other.get_wrapped());
    was_checked_ = true;
    return *this;
  }

  auto get() cpp_attribute_returns_nonnull { cpp_assert(was_checked_); return &(*t_); }
  T& get_wrapped() { return t_; }
  const T& get_wrapped() const { return t_; }
  auto operator*() { cpp_assert(was_checked_); return *t_; }
  auto operator*() const { cpp_assert(was_checked_); return *t_; }
  auto operator->() cpp_attribute_returns_nonnull { cpp_assert(was_checked_); return &(*t_); }
  auto operator->() const cpp_attribute_returns_nonnull { cpp_assert(was_checked_); return &(*t_); }

  explicit operator bool()
  {
    was_checked_ = true;
    return t_ != nullptr;
  }

private:
  T t_;

#ifndef NDEBUG
  bool was_checked_;
#endif
};

} // namespace cpp

#endif /* CPP_UTILS_MEMORY_MAYBE_NULL_H_ */
