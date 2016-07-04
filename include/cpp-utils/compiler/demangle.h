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

#ifndef CPP_UTILS_COMPILER_DEMANGLE_H_
#define CPP_UTILS_COMPILER_DEMANGLE_H_

#include <exception>

#ifdef __GNUC__

#include <cxxabi.h>
#include <cstdlib>
#include <memory>
#include <string>

#include "../memory/malloc_ptr.h"

namespace cpp {

inline std::string demangle(const char* mangled_name)
{
  int status;
  malloc_ptr<char> result = abi::__cxa_demangle(mangled_name, 0, 0, &status);
  return (status == 0 && result) ? std::string(result) : std::string();
}

inline std::string demangle_or_throw(const char* mangled_name)
{
  int status;
  malloc_ptr<char> result = abi::__cxa_demangle(mangled_name, 0, 0, &status);

  switch (status)
  {
  case 0:
    return std::string(result);

  case -1:
    throw std::bad_alloc();

  case -2:
    throw std::invalid_argument("mangled_name is not a valid name under the C++ ABI mangling rules");

  case -3:
    throw std::invalid_argument();

  default:
    throw std::runtime_error();
  }
}

#else
#error "not supported compiler for demangling C++ symbols"
#endif

} // namespace cpp



#endif /* CPP_UTILS_COMPILER_DEMANGLE_H_ */
