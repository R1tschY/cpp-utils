#ifndef ZERO_H
#define ZERO_H

#include <memory>
#include <cstring>

namespace cpp {

template<typename T> inline
T& zero(T& obj) {
  std::memset(std::addressof(obj), 0, sizeof(T));
  return obj;
}

} // namespace extra

#endif // ZERO_H
