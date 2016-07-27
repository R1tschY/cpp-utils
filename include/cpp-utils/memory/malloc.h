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

#ifndef CPP_UTILS_MEMORY_MALLOC_PTR_H_
#define CPP_UTILS_MEMORY_MALLOC_PTR_H_

#include <cstdlib>
#include <new>
#include <memory>

#include "unique_array.h"

namespace cpp {

struct malloc_deleter
{
  template<typename T>
  void operator()(T* ptr) { std::free(ptr); }
};

template<typename T>
using malloc_ptr = std::unique_ptr<T, malloc_deleter>;

template<typename T>
using malloc_array = unique_array<T, malloc_deleter>;

/// \details credits to Stephen Lavavej (STL Features and Implementation
/// techniques talk at CppCon 2014)
template <class T>
struct mallocator
{
  typedef T value_type;

  mallocator() noexcept { } // default ctor not required

  template <class U>
  mallocator(const mallocator<U>&) noexcept { }

  template <class U>
  bool operator==(const mallocator<U>&) const noexcept { return true; }

  template <class U>
  bool operator!=(const mallocator<U>&) const noexcept { return false; }

  /// \todo migrate to a simple call to T-independent function: static_cast<T*>(mallocate(sizeof(T), n)
  T* allocate(size_t n) const
  {
    if (n == 0)
      return nullptr;

    if (n > static_cast<size_t>(-1) / sizeof(T))
      throw std::bad_array_new_length();

    void* pv = std::malloc(n * sizeof(T));

    if (!pv)
      throw std::bad_alloc();

    return static_cast<T*>(pv);
  }

  void deallocate(T* p, size_t) const noexcept
  {
    std::free(p);
  }
};

} // namespace cpp

#endif /* CPP_UTILS_MEMORY_MALLOC_PTR_H_ */
