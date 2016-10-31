#ifndef STRINGLITERAL_H
#define STRINGLITERAL_H

#include <cstddef>
#include <utility>

namespace cpp {
namespace detail {

template<typename Str, std::size_t...I>
auto _build_string(std::index_sequence<I...>) {
  return std::integer_sequence<char, Str().chars[I]...>();
}

template<typename Str, std::size_t N>
auto build_string() {
  return _build_string<Str>(std::make_index_sequence<N>());
}

#define lit(s) []{struct S{const char*chars=s;};return cpp::detail::build_string<S,strlen(s)>();}()

} // namespace detail
} // namespace cpp

#endif // STRINGLITERAL_H
