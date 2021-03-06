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

#ifndef CPP_UTILS_CONSTEXPR_ARRAY_H_
#define CPP_UTILS_CONSTEXPR_ARRAY_H_

namespace cpp {
namespace constxpr {

template<typename T, std::size_t N>
struct carray
{
public:

  constexpr T& operator[](std::size_t n)
  {
    if (n >= N) throw std::range_error("n >= N");
    return data[n];
  }

  constexpr const T& operator[](std::size_t n) const
  {
    if (n >= N) throw std::range_error("n >= N");
    return data[n];
  }

  // creators

  template<std::size_t M>
  constexpr
  carray<T, N+M> append(const carray<T, M>& other) const
  {
    carray<T, N+M> result{};

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
  T data[N];
};

template<typename T, std::size_t N>
constexpr inline
carray<T, N> make_carray(const T (&data)[N])
{
  carray<T, N> result{};

  for (std::size_t i = 0; i < N; ++i)
  {
    result[i] = data[i];
  }

  return result;
}

} // namespace constxpr
} // namespace cpp

#endif /* CPP_UTILS_CONSTEXPR_ARRAY_H_ */
