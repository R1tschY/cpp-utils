/*
 *      Copyright 2015 R1tschY <r1tschy@yahoo.de>
 *      
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef BLOCKS_R1TSCHY_CPP_UTILS_INCLUDE_CPP_UTILS_MEMORY_GET_H_
#define BLOCKS_R1TSCHY_CPP_UTILS_INCLUDE_CPP_UTILS_MEMORY_GET_H_

#include <type_traits>
#include "../meta/core.h"

namespace cpp {

namespace detail {

template<typename T, typename = void>
struct has_get_method : std::false_type { };

template<typename T>
struct has_get_method<T, void_t<decltype(std::declval<T>().get())>>
: std::true_type { };

} // namespace detail

template<typename T, typename std::enable_if<!detail::has_get_method<T>::value>::type* = nullptr>
auto get(T&& t) -> decltype(t)
{
  return t;
}

template<typename T, typename std::enable_if<detail::has_get_method<T>::value>::type* = nullptr>
auto get(T&& t) -> decltype(t.get())
{
  return t.get();
}

} // namespace cpp

#endif /* BLOCKS_R1TSCHY_CPP_UTILS_INCLUDE_CPP_UTILS_MEMORY_GET_H_ */
