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
#include <utility>

#include "constexpr/cstring.h"

namespace cpp {

template<typename T>
struct type_t
{
  using type = T;
};

// support

// string literal: lit("string")

template<char...Chars>
inline constexpr
constxpr::cstring<sizeof...(Chars)> fmtstr(type_t<std::integer_sequence<char, Chars...>>)
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

// integers

#define CPP_MAKE_INT_FMT(type, fmt) \
  inline constexpr constxpr::cstring<strlen(fmt)> fmtstr(type_t<type>) \
  { return constxpr::make_cstring(fmt); } \
  inline std::tuple<type> fmtargs(const type& data) \
  { return std::tuple<type>(data); }

CPP_MAKE_INT_FMT(char, "%c")

CPP_MAKE_INT_FMT(signed char, "%hhd")
CPP_MAKE_INT_FMT(short, "%hd")
CPP_MAKE_INT_FMT(int, "%d")
CPP_MAKE_INT_FMT(long, "%ld")
CPP_MAKE_INT_FMT(long long, "%lld")

CPP_MAKE_INT_FMT(unsigned char, "%hhu")
CPP_MAKE_INT_FMT(unsigned short, "%hu")
CPP_MAKE_INT_FMT(unsigned int, "%u")
CPP_MAKE_INT_FMT(unsigned long, "%lu")
CPP_MAKE_INT_FMT(unsigned long long, "%llu")

CPP_MAKE_INT_FMT(float, "%f")
CPP_MAKE_INT_FMT(double, "%f")

#undef CPP_MAKE_INT_FMT

// string

inline constexpr
constxpr::cstring<2> fmtstr(type_t<char*> data)
{
  return constxpr::make_cstring("%s");
}

inline constexpr
constxpr::cstring<2> fmtstr(type_t<const char*> data)
{
  return constxpr::make_cstring("%s");
}

inline
std::tuple<const char*> fmtargs(const char* data)
{
  return std::make_tuple(data);
}

// pointer

template<typename T>
inline constexpr
constxpr::cstring<2> fmtstr(type_t<T*> data)
{
  return constxpr::make_cstring("%p");
}

template<typename T>
inline
std::tuple<const void*> fmtargs(const T* data)
{
  return std::make_tuple(data);
}

// internals

namespace detail {

template<typename Tail>
inline constexpr
auto build_fmtstr(Tail tail)
{
  // last element
  return fmtstr(tail);
}

template<typename Head, typename...Tail>
inline constexpr
auto build_fmtstr(Head head, Tail...tail)
{
  return fmtstr(head).append(build_fmtstr(tail...));
}

template<typename Func, typename Tuple, std::size_t... I>
constexpr auto printf_apply(Func&& func, Tuple&& t, std::index_sequence<I...>)
{
  return std::forward<Func>(func)(std::get<I>(std::forward<Tuple>(t))...);
}

template<typename Func, typename Tuple>
constexpr auto printf_apply(Func&& func, Tuple&& t)
{
  return printf_apply(
    std::forward<Func>(func),
    std::forward<Tuple>(t),
    std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>{}>{});
}

struct printf
{
  printf(const char* fmt) : fmt_(fmt)
  { }

  template<typename...Args>
  int operator()(Args...args)
  {
    return std::printf(fmt_, std::forward<Args>(args)...);
  }

  const char* fmt_;
};

struct sprintf
{
  sprintf(char* buffer, std::size_t buffer_size, const char* fmt) :
    fmt_(fmt),
    buffer_(buffer),
    buffer_size_(buffer_size)
  { }

  template<typename...Args>
  int operator()(Args...args)
  {
    return std::snprintf(buffer_, buffer_size_, fmt_, std::forward<Args>(args)...);
  }

  const char* fmt_;
  char* buffer_;
  std::size_t buffer_size_;
};

} // namespace detail

// interface

template<typename...Args>
int printf(const Args&...args)
{
  // build format string (compile time)
  constexpr auto fmt = detail::build_fmtstr(type_t<std::decay_t<Args>>()...);

  // actual printf call (runtime)
  return detail::printf_apply(
    detail::printf(fmt.data),
    std::tuple_cat(fmtargs(args)...));
}

template<std::size_t N, typename...Args>
int sprintf(char (&buffer)[N], const Args&...args)
{
  // build format string (compile time)
  constexpr auto fmt = detail::build_fmtstr(type_t<std::decay_t<Args>>()...);

  // actual printf call (runtime)
  return detail::printf_apply(
    detail::sprintf(buffer, N, fmt.data),
    std::tuple_cat(fmtargs(args)...));
}

} // namespace cpp

#endif /* CPP_UTILS_CONSTEXPR_PRINTF_BUILDER_H_ */
