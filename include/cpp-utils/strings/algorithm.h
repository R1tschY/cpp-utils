///
/// Copyright (c) 2016 R1tschY
/// 
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to 
/// deal in the Software without restriction, including without limitation the 
/// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
/// sell copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
/// IN THE SOFTWARE.
///


#pragma once

#include <cstddef>
#include <string>
#include <algorithm>
#include <utility>
#include "../algorithm/length.h"
#include "../resolve.h"
#include "../call.h"

namespace cpp {
namespace string {

// functors

using isspace = call<int(int)>::get<&std::isspace>;

// functions

template<typename StringView, typename Strings, typename String>
void join(const StringView& del, const Strings& strings, String& result)
{
  // TODO: if not hasattr(strings, 'size'): strings = list(strings)
  result.clear();

  // skip special case
  size_t strings_size = cpp::length(strings);
  if (strings_size == 0)
    return;

  // calculate result size
  // TODO: #ifdef cpp::has_reserve<Strings>::value
  // TODO: result_size = sum(map(cpp::length, strings)) + ...
  size_t result_size = (strings_size - 1) * cpp::length(del);
  for (const auto& string : strings)
  {
    result_size += cpp::length(string);
  }

  // create result object
  result.reserve(result_size); // TODO: cpp::reserve

  // create result
  auto first = strings.begin();
  auto end = strings.end();

  result.append(first->begin(), first->end());
  ++first;

  for (; first != end; ++first)
  {
    // TODO: cpp::string::append
    // -> result.append(begin,end) OR result += string OR result.push_back(string[i])
    result.append(del.begin(), del.end());
    result.append(first->begin(), first->end());
  }
}

template<typename Char, typename String>
void lpad(Char padchar, size_t dest_size, String& result)
{
  size_t size = cpp::length(result);
  if (size > dest_size)
    return;

  result.insert(result.begin(), dest_size - size, padchar);
}

template<typename Char, typename String, typename StringResult=String>
StringResult lpad(Char padchar, size_t dest_size, const String& string)
{
  size_t size = cpp::length(string);
  if (size > dest_size)
    return StringResult(string);

  StringResult result;
  result.reserve(dest_size);
  result.append(dest_size - size, padchar);
  result.append(string);
  return result;
}

template<typename Char, typename String>
void rpad(Char padchar, size_t dest_size, String& result)
{
  size_t size = cpp::length(result);
  if (size > dest_size)
    return;

  result.append(dest_size - size, padchar);
}

template<typename Char, typename String, typename StringResult=String>
StringResult rpad(Char padchar, size_t dest_size, const String& string)
{
  size_t size = cpp::length(string);
  if (size > dest_size)
    return StringResult(string);

  StringResult result;
  result.reserve(dest_size);
  result.append(string);
  result.append(dest_size - size, padchar);
  return result;
}

template<typename String, typename Func>
void ltrim(String& string, Func&& func)
{
  auto iter = std::find_if_not(std::begin(string), std::end(string), std::move(func));
  string.erase(string.begin(), iter);
}

template<typename String>
void ltrim(String& string)
{
  ltrim(string, isspace());
}

template<typename String, typename Func, typename StringResult=String>
StringResult ltrim(const String& string, Func&& func=isspace())
{
  auto iter = std::find_if_not(std::begin(string), std::end(string), std::move(func));
  return StringResult(iter, string.end());
}

template<typename String, typename StringResult=String>
StringResult ltrim(const String& string)
{
  return ltrim(string, isspace());
}

template<typename String, typename Func>
void rtrim(String& string, Func&& func=isspace())
{
  auto iter = std::find_if_not(std::rbegin(string), std::rend(string), std::move(func));
  string.erase(iter.base(), string.end());
}

template<typename String>
void rtrim(String& string)
{
  rtrim(string, isspace());
}

template<typename String, typename Func, typename StringResult=String>
StringResult rtrim(const String& string, Func&& func=isspace())
{
  auto iter = std::find_if_not(std::rbegin(string), std::rend(string), std::move(func));
  return StringResult(string.begin(), iter.base());
}

template<typename String, typename StringResult=String>
StringResult rtrim(const String& string)
{
  return rtrim(string, isspace());
}

template<typename StringView1, typename StringView2>
bool has_prefix(const StringView2& prefix, const StringView1& string)
{
  size_t size = cpp::length(string);
  size_t prefix_size = cpp::length(prefix);
  if (size < prefix_size)
    return false;

  return std::equal(
    std::begin(string), std::begin(string) + prefix_size,
    std::begin(prefix));
}

template<typename StringView1, typename StringView2>
bool has_suffix(const StringView2& suffix, const StringView1& string)
{
  size_t size = cpp::length(string);
  size_t suffix_size = cpp::length(suffix);
  if (size < suffix_size)
    return false;

  return std::equal(
    std::end(string) - suffix_size, std::end(string),
    std::begin(suffix));
}

template<typename StringView, typename String>
void ensure_prefix(const StringView& prefix, String& string)
{
  if (has_prefix(prefix, string))
    return;

  string.insert(std::begin(string), std::begin(prefix), std::end(prefix));
}

template<typename StringView, typename String>
void ensure_suffix(const StringView& suffix, String& string)
{
  if (has_suffix(suffix, string))
    return;

  string.append(std::begin(suffix), std::end(suffix));
}

template<typename StringView, typename String>
void remove_prefix(const StringView& prefix, String& string)
{
  if (!has_prefix(prefix, string))
    return;

  string.erase(std::begin(string), std::begin(string) + cpp::length(prefix));
}

template<typename StringView, typename String>
void remove_suffix(const StringView& suffix, String& string)
{
  if (!has_suffix(suffix, string))
    return;

  string.erase(std::end(string) - cpp::length(suffix), std::end(string));
}

} // namespace string
} // namespace cpp




