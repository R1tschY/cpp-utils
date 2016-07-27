///
/// Copyright (c) 2016 R1tschY
/// 
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to 
/// deal in the Software without restriction, including without limitation the 
/// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
/// sell copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
/// IN THE SOFTWARE.
///

#ifndef INCLUDE_CPP_UTILS_ARRAY_VIEW_H_
#define INCLUDE_CPP_UTILS_ARRAY_VIEW_H_

#include <cstddef>
#include <type_traits>
#include "algorithm/length.h"
#include "assert.h"

namespace cpp {

template<typename T>
class array_view {
  using T_nonconst = typename std::remove_const<T>::type;

public:
  explicit constexpr array_view() :
    ptr_(nullptr), size_(0)
  { }

  template<typename Range>
  explicit constexpr array_view(const Range& range) :
    ptr_(std::begin(range)), size_(length(range))
  { }

  explicit constexpr array_view(T* ptr, std::size_t size) :
    ptr_(ptr), size_(size)
  { }

  constexpr T* begin() const { return ptr_; }
  constexpr T* cbegin() const { return ptr_; }
  constexpr T* end() const { return ptr_ + size_; }
  constexpr T* cend() const { return ptr_ + size_; }

  constexpr bool empty() const { return size_ == 0; }
  constexpr explicit operator bool () const { return empty(); }

  constexpr std::size_t size() const { return size_; }
  constexpr std::size_t length() const { return size_; }

  constexpr void clear() { ptr_ = nullptr; size_ = 0; }

  constexpr T* data() { return ptr_; }
  constexpr const T* data() const { return ptr_; }

  constexpr T& operator[](std::size_t index)
  {
    return *(ptr_ + index);
  }

  constexpr const T& operator[](std::size_t index) const {
    return *(ptr_ + index);
  }

  T& at(std::size_t index)
  {
    cpp_assert(index < size_);
    return *(ptr_ + index);
  }

  const T& at(std::size_t index) const {
    cpp_assert(index < size_);
    return *(ptr_ + index);
  }

private:
  T* ptr_;
  std::size_t size_;
};

} // namespace cpp

#endif /* INCLUDE_CPP_UTILS_ARRAY_VIEW_H_ */
