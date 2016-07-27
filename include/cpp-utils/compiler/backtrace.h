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

#ifndef INCLUDE_CPP_UTILS_COMPILER_BACKTRACE_H_
#define INCLUDE_CPP_UTILS_COMPILER_BACKTRACE_H_

#include "compiler.h"
#include "../memory/unique_array.h"

#ifdef CPP_GCC

#include <execinfo.h>

namespace cpp {

inline
void backtrace(std::vector<void*>& x, std::size_t n = 256)
{
  void* trace[n];
  std::size_t size = ::backtrace(trace, n);
  x.assign(trace, trace + size);
}

//inline
//void backtrace(std::vector<void*>& x, std::size_t n)
//{
//  x.resize(n);
//  std::size_t size = ::backtrace(x.data(), n);
//  x.resize(size);
//}

inline
malloc_array<char*> backtrace_symbols(std::size_t n = 256)
{
  void* trace[n];

  std::size_t size = ::backtrace(trace, n);
  char** symbols = ::backtrace_symbols(trace, size);

  return (symbols) ? malloc_array<char*>(symbols, size) : malloc_array<char*>();
}

inline
malloc_array<char*> backtrace_symbols(array_view<void*> x)
{
  char** symbols = ::backtrace_symbols(x.data(), x.size());
  return (symbols) ? malloc_array<char*>(symbols, x.size()) : malloc_array<char*>();
}

} // namespace cpp

#endif

#endif /* INCLUDE_CPP_UTILS_COMPILER_BACKTRACE_H_ */
