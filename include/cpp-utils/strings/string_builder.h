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

#ifndef CPP_UTILS_STRINGS_STRING_BUILDER_H_
#define CPP_UTILS_STRINGS_STRING_BUILDER_H_

#include <type_traits>
#include <cstring>
#include <string>
#include <utility>
#include <iostream>

#include "string_view.h"
#include "../meta/void.h"
#include "../algorithm/arguments.h"

namespace cpp {

// concatenable trait

template<typename T, typename Enable = void>
struct concatenable {};

template<typename T>
using concatenable_t = typename concatenable<T>::type;

// basic_string_builder

template<typename Result, typename Lhs, typename Rhs>
class string_builder_node
{
public:
  using concat = concatenable<string_builder_node<Result, Lhs, Rhs>>;

  string_builder_node(const Lhs& lhs_, const Rhs& rhs_)
  : lhs(lhs_), rhs(rhs_)
  { }

  Result build() const
  {
    // get length of resulting string
    std::size_t len = concat::size(*this);

    // construct string
    Result result;

#ifndef CPP_STRING_BUILDER_IMPL_PTR
    // reserve resulting length
    result.reserve(len);

    // create string
    concat::append(result, *this);
#else
    // reserve resulting length
    result.resize(len);

    // create string
    auto ptr = std::addressof(*result.begin());
    concat::append(ptr, *this);
#endif

    std::wstring r;
    return result;
  }

  const Lhs& lhs;
  const Rhs& rhs;
};

// general case

template<typename Result, typename Lhs, typename Rhs>
struct concatenable<string_builder_node<Result, Lhs, Rhs>>
{
    using type = string_builder_node<Result, Lhs, Rhs>;

    static std::size_t size(const type& p)
    {
      return concatenable<Lhs>::size(p.lhs) + concatenable<Rhs>::size(p.rhs);
    }

    static void append(Result& r, const type& p)
    {
      concatenable<Lhs>::append(r, p.lhs);
      concatenable<Rhs>::append(r, p.rhs);
    }

    template<typename CharT>
    static void append(CharT*& out, const type& p)
    {
      concatenable<Lhs>::append(out, p.lhs);
      concatenable<Rhs>::append(out, p.rhs);
    }
};

// std::basic_string support

//template<typename CharT, typename Traits, typename Alloc>
//struct concatenable<std::basic_string<CharT, Traits, Alloc>>
//{
//    typedef std::basic_string<CharT, Traits, Alloc> type;
//
//    static std::size_t size(const type& x) { return x.size(); }
//
//    template<typename Result>
//    static void appendTo(Result& result, const type& self)
//    {
//      result.append(self);
//    }
//
//    static void appendTo(CharT*& out, const type& self)
//    {
//      const int n = self.size();
//      memcpy(out, reinterpret_cast<const char*>(&*self.begin()), sizeof(CharT) * n);
//      out += n;
//    }
//};
//
//// std::basic_string_view support
//
//template<typename CharT, typename Traits>
//struct concatenable<cpp::basic_string_view<CharT, Traits>>
//{
//    typedef cpp::basic_string_view<CharT, Traits> type;
//
//    static std::size_t size(const type& x) { return x.size(); }
//
//    template<typename Result>
//    static void appendTo(Result& result, const type& self)
//    {
//      result.append(self.begin(), self.end());
//    }
//
//    static void appendTo(CharT*& out, const type& self)
//    {
//      const int n = self.size();
//      memcpy(out, reinterpret_cast<const char*>(&*self.begin()), sizeof(CharT) * n);
//      out += n;
//    }
//};

// range support

template<typename T>
struct concatenable<T, void_t<decltype(std::begin(std::declval<T>()))>>
{
    typedef T type;
    using CharT = std::decay_t<decltype(*std::begin(std::declval<T>()))>;

    static std::size_t size(const type& x)
    {
      return std::size_t(std::distance(std::begin(x), std::end(x)));
    }

    template<typename Result>
    static void appendTo(Result& result, const type& x)
    {
      result.append(std::begin(x), std::end(x));
    }

    static void appendTo(CharT*& out, const type& x)
    {
      out = std::copy(std::begin(x), std::end(x), out);
    }
};

// const CharT* support

template<typename CharT>
struct concatenable<const CharT*>
{
    typedef const CharT* type;

    constexpr static std::size_t size(const CharT* x)
    { return std::char_traits<CharT>::length(x); }

    template<typename Result>
    static void appendTo(Result& result, const CharT* x)
    {
      result.append(x, x + size(x));
    }

    static void appendTo(CharT*& out, const CharT* x)
    {
      if (!x)
          return;
      while (*x)
          *out++ = *x++;
    }
};

template <typename CharT, int N>
struct concatenable<const CharT[N]>
{
    typedef const CharT type[N];

    constexpr static std::size_t size(const CharT[N])
    { return N - 1; }

    template<typename Result>
    static void appendTo(Result& result, const CharT x[N])
    {
      result.append(x, x + size(x));
    }

    static void appendTo(CharT*& out, const CharT x[N])
    {
      out = std::copy(std::begin(x), std::end(x), out);
    }
};

template <typename CharT, int N>
struct concatenable<CharT[N]>
{
    typedef const CharT type[N];

    constexpr static std::size_t size(const CharT[N])
    { return N - 1; }

    template<typename Result>
    static void appendTo(Result& result, const CharT x[N])
    {
      result.append(x, x + size(x));
    }

    static void appendTo(CharT*& out, const CharT x[N])
    {
      out = std::copy(std::begin(x), std::end(x), out);
    }
};

// CharT support

template<typename CharT>
struct concatenable_char
{
    typedef CharT type;

    constexpr static std::size_t size(CharT x)
    { return 1; }

    template<typename Result>
    static void appendTo(Result& result, CharT x)
    {
      result.push_back(x);
    }

    static void appendTo(CharT*& out, CharT c)
    {
      *out++ = c;
    }
};

template <> struct concatenable<char> : concatenable_char<char> { };
template <> struct concatenable<wchar_t> : concatenable_char<wchar_t> { };
template <> struct concatenable<char16_t> : concatenable_char<char16_t> { };
template <> struct concatenable<char32_t> : concatenable_char<char32_t> { };

// operators

template<typename Result, typename Lhs, typename Rhs>
string_builder_node<Result, concatenable_t<Lhs>, concatenable_t<Rhs>>
operator+(const Lhs& lhs, const Rhs& rhs)
{
   return string_builder_node<Result, concatenable_t<Lhs>, concatenable_t<Rhs>>(lhs, rhs);
}

template<typename T>
std::size_t string_length(const T& t)
{
  return concatenable<T>::size(t);
}

template<typename Result, typename T>
void string_append(Result& result, const T& t)
{
  concatenable<T>::appendTo(result, t);
}

template<typename Result, typename...Args>
Result concatenate(const Args&...args)
{
  std::size_t len = arguments::accumulate(
    [](const auto& arg){ return string_length(arg); },
    0,
    args...
  );

  // reserve size
  Result result;
  result.reserve(len);

  // build string
  arguments::for_each(
    [&result](const auto& arg){
      string_append(result, arg);
    },
    args...
  );

  return result;
}

template<typename Result, typename...Args>
void concatenate_to(Result& result, const Args&...args)
{
  std::size_t len = arguments::accumulate(
    [](const auto& arg){ return string_length(arg); },
    0,
    args...
  );

  // reserve size
  result.reserve(result.size() + len);

  // build string
  arguments::for_each(
    [&result](const auto& arg){
      string_append(result, arg);
    },
    args...
  );
}

template<typename Result, typename...Args>
Result concatenate_to(Result&& result, const Args&...args)
{
  std::size_t len = arguments::accumulate(
    [](const auto& arg){ return string_length(arg); },
    0,
    args...
  );

  // reserve size
  result.reserve(result.size() + len);

  // build string
  arguments::for_each(
    [&result](const auto& arg){
      string_append(result, arg);
    },
    args...
  );

  return std::move(result);
}

} // namespace cpp

#endif /* CPP_UTILS_STRINGS_STRING_BUILDER_H_ */
