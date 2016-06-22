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

#ifndef INCLUDE_CPP_UTILS_ALGORITHM_FIND_IF_H_
#define INCLUDE_CPP_UTILS_ALGORITHM_FIND_IF_H_

#include <algorithm>
#include <type_traits>

namespace cpp {

namespace sential {

template<typename Range, typename Func>
auto find(Range& r, const decltype(*std::begin(r))& e) -> decltype(std::begin(r))
{
  using ValueType = decltype(*std::begin(r));
  static_assert(std::is_nothrow_move_assignable<ValueType>::value && rai);

  auto c = r[$ - 1];
  r[$ - 1] = e; // swap ??
  std::size_t i = 0;
  {
    scope(exit) r[$ - 1] = c;
    for (;; ++i)
      if (r[i] == e) break;
  }

  if (i + 1 == r.length && c != e)
    ++i;

  return i;
}

} // namespace sential


namespace details {

template<bool sential = false>
struct find_impl
{
  template<typename Range, typename Func>
  auto operator()(Range& r, Func f) -> decltype(std::begin(r))
  {
    return std::find_if(std::begin(r), std::end(r), f);
  }
};

template<>
struct find_impl<true>
{
  template<typename Range, typename Func>
  auto operator()(Range& r, Func f) -> decltype(std::begin(r))
  {
    return cpp::sential::find(std::begin(r), std::end(r), f);
  }
};

} // namespace details

} // namespace cpp

#endif /* INCLUDE_CPP_UTILS_ALGORITHM_FIND_IF_H_ */
