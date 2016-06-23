#ifndef INCLUDE_CPP_UTILS_ALGORITHM_ARGUMENTS_H_
#define INCLUDE_CPP_UTILS_ALGORITHM_ARGUMENTS_H_

namespace cpp {

/// from https://twitter.com/SeanParent/status/558765089294020609
template<typename Fun, typename...Ts>
void foreach_argument(Fun&& f, Ts&&... args) {
  using t = int[sizeof...(Args)];
  (void)t{(f(forward<Args>(args)), 0)...};
}

}  // namespace cpp

#endif /* INCLUDE_CPP_UTILS_ALGORITHM_ARGUMENTS_H_ */
