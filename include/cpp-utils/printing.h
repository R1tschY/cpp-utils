#ifndef INCLUDE_CPP_UTILS_PRINTING_H_
#define INCLUDE_CPP_UTILS_PRINTING_H_

#include <iosfwd>
#include <memory>

// std printers

/// missing printer for nullptr
/// from https://cplusplus.github.io/LWG/lwg-active.html#2221
template<class C, class T>
std::basic_ostream<C, T>& operator<<(std::basic_ostream<C, T>& os, nullptr_t)
{
  return os << static_cast<void*>(nullptr);
}

template<class C>
std::basic_ostream<C>& operator<<(std::basic_ostream<C>& os, nullptr_t)
{
  return os << static_cast<void*>(nullptr);
}

template<class C, class T, class U>
std::basic_ostream<C, T>& operator<<(std::basic_ostream<C, T>& os, const std::unique_ptr<U>& u) {
    return os << u.get();
}

#endif /* INCLUDE_CPP_UTILS_PRINTING_H_ */
