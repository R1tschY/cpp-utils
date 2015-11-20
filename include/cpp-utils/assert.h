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

#ifndef BLOCKS_R1TSCHY_CPP_UTILS_INCLUDE_CPP_UTILS_ASSERT_H_
#define BLOCKS_R1TSCHY_CPP_UTILS_INCLUDE_CPP_UTILS_ASSERT_H_

#include "preprocessor.h"

namespace cpp {

#ifndef NDEBUG
# define cpp_assert(expr) (expr) \
  ? CPP_NOOP \
  : CPP_ASSERT_FAIL(CPP_STRINGIFY(expr), __PRETTY_FUNCTION__, __LINE__, __FILE__)
#else
# define cpp_assert(expr) CPP_NOOP
#endif

void assert_fail_abort(const char* expr, const char* func, int line, const char* file);
void assert_fail_throw(const char* expr, const char* func, int line, const char* file);

#ifdef CPP_ASSERT_ABORT
# define CPP_ASSERT_FAIL ::cpp::assert_fail_abort
#elif defined(CPP_ASSERT_THROW)
# define CPP_ASSERT_FAIL ::cpp::assert_fail_throw
#else
# define CPP_ASSERT_FAIL ::cpp::assert_fail_abort
#endif

} // namespace cpp

#endif /* BLOCKS_R1TSCHY_CPP_UTILS_INCLUDE_CPP_UTILS_ASSERT_H_ */
