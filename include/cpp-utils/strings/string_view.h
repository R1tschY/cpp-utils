#ifndef LIBS_CPP_UTILS_INCLUDE_CPP_UTILS_STRINGS_STRING_VIEW_H_
#define LIBS_CPP_UTILS_INCLUDE_CPP_UTILS_STRINGS_STRING_VIEW_H_

#include <experimental/string_view>
#include <string>

namespace cpp {

template<typename CharT, typename Traits = std::char_traits<CharT>>
using basic_string_view = std::experimental::basic_string_view<CharT, Traits>;

using string_view = std::experimental::basic_string_view<char>;
using wstring_view = std::experimental::basic_string_view<wchar_t>;

} // namespace cpp

#endif /* LIBS_CPP_UTILS_INCLUDE_CPP_UTILS_STRINGS_STRING_VIEW_H_ */
