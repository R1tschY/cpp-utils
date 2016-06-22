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

#ifndef INCLUDE_CPP_UTILS_DOWN_CAST_H_
#define INCLUDE_CPP_UTILS_DOWN_CAST_H_

#include "assert.h"

namespace cpp {

/// \brief a checked \c dynamic_cast
///
/// \details if \c NDEBUG is defined, no check is done.
/// \todo allow non-polymorphic types and do only a static_cast
/// \todo check if \p T is base of \p U
///
template<typename U, typename T>
U* down_cast(T* t)
{
#ifndef NDEBUG
  auto* u = dynamic_cast<U*>(t);
  cpp_assert(u != nullptr);
  return u;
#else
  return static_cast<U*>(t);
#endif
}

/// \copydoc down_cast(T*)
template<typename U, typename T>
U& down_cast(T& t)
{
#ifndef NDEBUG
  auto* u = dynamic_cast<U*>(&t);
  cpp_assert(u != nullptr);
  return *u;
#else
  return static_cast<U*>(&t);
#endif
}

} // namespace cpp

#endif /* INCLUDE_CPP_UTILS_DOWN_CAST_H_ */
