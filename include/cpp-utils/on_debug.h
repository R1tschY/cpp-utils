#ifndef LIBS_CPP_UTILS_ON_DEBUG_H_
#define LIBS_CPP_UTILS_ON_DEBUG_H_

#ifndef NDEBUG
// Debug mode
#define ON_DEBUG(...) __VA_ARGS__
#else
// no debug mode
#define ON_DEBUG(...)
#endif

#endif /* LIBS_CPP_UTILS_ON_DEBUG_H_ */
