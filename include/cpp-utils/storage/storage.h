#ifndef CPP_STORAGE_H
#define CPP_STORAGE_H

#include <type_traits>

namespace cpp {

template<typename T>
using storage = typename std::aligned_storage<sizeof(T), alignof(T)>::type;

template<typename T>
T& get(storage<T>& s) {
  return *reinterpret_cast<T*>(&s);
}

template<typename T>
const T& get(const storage<T>& s) {
  return *reinterpret_cast<const T*>(&s);
}

} // namespace cpp

#endif // CPP_STORAGE_H
