#pragma once

namespace cpp {

//
// get_ptr

template<typename T>
T* get_ptr(T* ptr)
{
  return ptr;
}

// std::unique_ptr, std::shared_ptr, ...
template<typename T>
auto get_ptr(const T& ptr)
{
  return ptr.get();
}

}  // namespace cpp
