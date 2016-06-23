#ifndef INCLUDE_CPP_UTILS_META_VOID_H_
#define INCLUDE_CPP_UTILS_META_VOID_H_

namespace cpp {

// meta programming support

template<typename... Ts> struct make_void { typedef void type; };
template<typename... Ts> using void_t = typename make_void<Ts...>::type;

} // namespace cpp

#endif /* INCLUDE_CPP_UTILS_META_VOID_H_ */
