#ifndef INCLUDE_CPP_UTILS_ALGORITHM_ARGUMENTS_H_
#define INCLUDE_CPP_UTILS_ALGORITHM_ARGUMENTS_H_

#include <cstddef>
#include <utility>

namespace cpp {

namespace arguments {

/// from https://twitter.com/SeanParent/status/558765089294020609
template<typename Fun, typename...Ts>
void for_each(Fun&& f, Ts&&... args) {
  using t = int[sizeof...(Ts)];
  (void)t{(f(std::forward<Ts>(args)), 0)...};
}

template<typename Fun, typename...Args>
std::size_t accumulate(Fun&& fmap, std::size_t init, Args&&... args) {
  using t = int[sizeof...(Args)];
  (void)t{(init += fmap(std::forward<Args>(args)), 0)...};
  return init;
}

} // namespace arguments

}  // namespace cpp

#endif /* INCLUDE_CPP_UTILS_ALGORITHM_ARGUMENTS_H_ */
