#ifndef LIBS_CPP_UTILS_NORMALIZE_H_
#define LIBS_CPP_UTILS_NORMALIZE_H_

namespace cpp {

/// provide the compiler with branch prediction information
#ifdef __GNUC__
# define cpp_likely(x) __builtin_expect(!!(x), 1)
#else
# define cpp_likely(x) (x)
#endif

/// provide the compiler with branch prediction information
#ifdef __GNUC__
# define cpp_unlikely(x) __builtin_expect(!!(x), 0)
#else
# define cpp_unlikely(x) (x)
#endif

}  // namespace cpp

#endif /* LIBS_CPP_UTILS_NORMALIZE_H_ */
