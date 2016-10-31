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

#pragma once

#include <utility>

namespace cpp {
namespace constxpr {

template<typename Char, std::size_t N>
struct basic_cstring
{
public:
  constexpr basic_cstring() : data{}
  { }

  constexpr basic_cstring(std::initializer_list<Char> list) : data{}
  {
    if (list.size() != N)
      throw std::range_error("list.size() != N");

    std::size_t i = 0;
    for (Char c : list)
    {
      data[i] = c;
      i += 1;
    }
  }

  constexpr basic_cstring(const char* str) : data{}
  {
    if (std::strlen(str) != N)
      throw std::range_error("strlen(str) != N");

    for (std::size_t i = 0; i < N; ++i)
    {
      data[i] = str[i];
    }
  }

  constexpr Char& operator[](std::size_t n)
  {
    //if (n >= N) throw std::range_error("n > N");
    return data[n];
  }

  constexpr const Char& operator[](std::size_t n) const
  {
    //if (n >= N) throw std::range_error("n > N");
    return data[n];
  }

  // creators

  template<std::size_t M>
  constexpr
  basic_cstring<Char, N+M> append(const basic_cstring<Char, M>& other) const
  {
    basic_cstring<Char, N+M> result{};

    for (std::size_t i = 0; i < N; ++i)
    {
      result[i] = data[i];
    }

    for (std::size_t i = 0; i < M; ++i)
    {
      result[N + i] = other[i];
    }

    return result;
  }

  // data
  Char data[N + 1];
};

template<typename Char, std::size_t N>
constexpr inline
basic_cstring<Char, N-1> make_cstring(const Char (&data)[N])
{
  return basic_cstring<Char, N-1>{data};
}

template<std::size_t N>
using cstring = basic_cstring<char, N>;

template<std::size_t N>
using cwstring = basic_cstring<wchar_t, N>;

} // namespace constxpr
} // namespace cpp


