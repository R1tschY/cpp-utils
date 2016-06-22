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

#ifndef CPP_UTILS_ATTRIBUTES_H_
#define CPP_UTILS_ATTRIBUTES_H_

#ifdef __GCC__
# define cpp_attribute_nonnull(...) __attribute__((nonnull(__VA_ARGS__)))
#else
# define cpp_attribute_nonnull(...)
#endif

#ifdef __GCC__
# define cpp_attribute_returns_nonnull __attribute__((returns_nonnull))
#else
# define cpp_attribute_returns_nonnull
#endif

#ifdef __GNUC__
#define cpp_attribute_hot __attribute__((hot))
#else
#define cpp_attribute_hot
#endif

/// \brief function attribute to always inline a function
#ifdef __GNUC__
# define cpp_force_inline __attribute__((always_inline)) inline
#else
# define cpp_force_inline inline
#endif

#endif // CPP_UTILS_ATTRIBUTES_H_
