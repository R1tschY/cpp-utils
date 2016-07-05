#ifndef LIBS_CPP_UTILS_INCLUDE_CPP_UTILS_STRINGS_STRING_VIEW_H_
#define LIBS_CPP_UTILS_INCLUDE_CPP_UTILS_STRINGS_STRING_VIEW_H_

#include <experimental/string_view>
#include <string>

namespace cpp {

template<typename CharT, typename Traits = std::char_traits<CharT>>
using basic_string_view = std::experimental::basic_string_view<CharT, Traits>;

using string_view = std::experimental::basic_string_view<char>;
using wstring_view = std::experimental::basic_string_view<wchar_t>;

inline namespace string_view_literals {
using namespace std::experimental::literals::string_view_literals;
}

template<typename CharT, typename Traits, typename Alloc>
std::basic_string<CharT, Traits, Alloc> operator+(const std::basic_string<CharT, Traits, Alloc>& rhs, basic_string_view<CharT, Traits> lhs)
{
  std::basic_string<CharT, Traits, Alloc> result;
  result.reserve(rhs.size() + lhs.size());
  result.append(rhs);
  result.append(lhs.data(), lhs.size());
  return result;
}

template<typename CharT, typename Traits, typename Alloc>
std::basic_string<CharT, Traits, Alloc> operator+(std::basic_string<CharT, Traits, Alloc>&& rhs, basic_string_view<CharT, Traits> lhs)
{
  std::basic_string<CharT, Traits, Alloc> result = std::move(rhs);
  result.append(lhs.data(), lhs.size());
  return result;
}

template<typename CharT, typename Traits, typename Alloc>
std::basic_string<CharT, Traits, Alloc> operator+(basic_string_view<CharT, Traits> lhs, const std::basic_string<CharT, Traits, Alloc>& rhs)
{
  std::basic_string<CharT, Traits, Alloc> result;
  result.reserve(rhs.size() + lhs.size());
  result.append(lhs.data(), lhs.size());
  result.append(rhs);
  return result;
}

template<typename CharT, typename Traits, typename Alloc>
std::basic_string<CharT, Traits, Alloc> operator+(basic_string_view<CharT, Traits> lhs, std::basic_string<CharT, Traits, Alloc>&& rhs)
{
  std::basic_string<CharT, Traits, Alloc> result = std::move(rhs);
  result.insert(result.begin(), lhs.data(), lhs.size());
  return result;
}

} // namespace cpp

#endif /* LIBS_CPP_UTILS_INCLUDE_CPP_UTILS_STRINGS_STRING_VIEW_H_ */
