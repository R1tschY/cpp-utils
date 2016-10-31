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
#include <string>
#include <tuple>
#include <memory>

#include "constexpr/cstring.h"

namespace cpp {

// std support

// std::string

inline constexpr
constxpr::cstring<2> fmtstr(const std::string&)
{
  return constxpr::make_cstring("%s");
}

inline
std::tuple<const char*> fmtargs(const std::string& s)
{
  return std::make_tuple(s.c_str());
}

// std::unique_ptr

template<typename T>
inline constexpr
constxpr::cstring<2> fmtstr(const std::unique_ptr<T>&)
{
  return constxpr::make_cstring("%p");
}

template<typename T>
inline
std::tuple<const void*> fmtargs(const std::unique_ptr<T>& t)
{
  return std::make_tuple(t.get());
}

// std::shared_ptr

template<typename T>
inline constexpr
constxpr::cstring<2> fmtstr(const std::shared_ptr<T>&)
{
  return constxpr::make_cstring("%p");
}

template<typename T>
inline
std::tuple<const void*> fmtargs(const std::shared_ptr<T>& t)
{
  return std::make_tuple(t.get());
}

} // namespace cpp

#endif /* CPP_UTILS_CONSTEXPR_PRINTF_BUILDER_H_ */
