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

#ifndef CPP_UTILS_CONSTEXPR_PRINTF_BUILDER_H_
#define CPP_UTILS_CONSTEXPR_PRINTF_BUILDER_H_

#include <type_traits>
#include <cstring>
#include <string>
#include <utility>
#include <iostream>

#include "array.h"
#include "../meta/void.h"
#include "../algorithm/arguments.h"

namespace cpp {

template<std::size_t N, typename...Ts>
using fmtstyle = std::pair<constexpr_array<char, N>, std::tuple<Ts...>>;

template<char...Chars>
inline constexpr
constexpr_array<char, sizeof...(Chars)> fmtstr(const std::integer_sequence<char, Chars...>&)
{
  // FIXME: escape % to %%
  return { { Chars... } };
}

template<char...Chars>
inline
std::tuple<> fmtargs(const std::integer_sequence<char, Chars...>&)
{
  return std::make_tuple();
}

inline constexpr
constexpr_array<char, 2> fmtstr(const int&)
{
  return { { '%', 'd' } };
}

inline
std::tuple<int> fmtargs(const int& data)
{
  return std::make_tuple(data);
}

inline constexpr
constexpr_array<char, 2> fmtstr(const char* data)
{
  return { { '%', 's' } };
}

inline
std::tuple<const char*> fmtargs(const char* data)
{
  return std::make_tuple(data);
}

template<typename...Tail>
inline constexpr
auto build_fmtstr(Tail&&...tail)
{
  return constexpr_array<char, 0>();
}

template<typename Head, typename...Tail>
inline constexpr
auto build_fmtstr(const Head& head, const Tail&...tail)
{
  return fmtstr(head).append(build_fmtstr(tail...));
}

template<typename...Args>
inline
auto build_printf_args(const Args&...args)
{
  return std::tuple_cat(fmtargs(args)...);
}

template <class Tuple, std::size_t... I>
constexpr auto call_printf(const char* fmt, Tuple&& t, std::index_sequence<I...>)
{
  return ::printf(fmt, std::get<I>(std::forward<Tuple>(t))...);
}

template <class Tuple>
constexpr auto call_printf(const char* fmt, Tuple&& t)
{
    return call_printf(fmt, std::forward<Tuple>(t),
        std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>{}>{});
}

template<typename...Args>
int printf(const Args&...args)
{
  static constexpr auto fmt = build_fmtstr(args..., std::integer_sequence<char, '\0'>{});

  return call_printf(fmt.data, build_printf_args(args...));
}

} // namespace cpp

#endif /* CPP_UTILS_CONSTEXPR_PRINTF_BUILDER_H_ */
