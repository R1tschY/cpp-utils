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

#ifndef BLOCKS_R1TSCHY_CPP_UTILS_INCLUDE_CPP_UTILS_MEMORY_NOT_NULL_H_
#define BLOCKS_R1TSCHY_CPP_UTILS_INCLUDE_CPP_UTILS_MEMORY_NOT_NULL_H_

#include "../assert.h"
#include "../detail/normalize.h"

namespace cpp {

template<typename T>
class not_null
{
public:
  not_null(T t) cpp_attribute_nonnull(1)
  : t_(t)
  {
    cpp_assert(t != nullptr);
  }

  not_null(const maybe_null<T>& t)
  : t_(t.get_wrapped())
  {
    cpp_assert(t != nullptr);
  }

  not_null(maybe_null<T>&& t)
  : t_(std::move(t.get_wrapped()))
  {
    cpp_assert(t != nullptr);
  }

  auto get() cpp_attribute_returns_nonnull { return &(*t_); }
  T& get_wrapped() { return t_; }
  const T& get_wrapped() const { return t_; }
  auto operator*() { return *t_; }
  auto operator*() const { return *t_; }
  auto operator->() cpp_attribute_returns_nonnull { return &(*t_); }
  auto operator->() cpp_attribute_returns_nonnull const { return &(*t_); }

  explicit auto operator bool()
  {
    return true;
  }

private:
  T t_;
};

} // namespace cpp

#endif /* BLOCKS_R1TSCHY_CPP_UTILS_INCLUDE_CPP_UTILS_MEMORY_NOT_NULL_H_ */
