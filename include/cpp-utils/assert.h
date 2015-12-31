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

#ifndef CPP_UTILS_ASSERT_H_
#define CPP_UTILS_ASSERT_H_

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <sstream>
#include "preprocessor.h"

namespace cpp {

#ifndef NDEBUG
# define cpp_assert(expr) (expr) \
  ? CPP_NOOP \
  : CPP_ASSERT_FAIL(CPP_STRINGIFY(expr), __PRETTY_FUNCTION__, __FILE__, __LINE__)
#else
# define cpp_assert(expr) CPP_NOOP
#endif


class assert_failure : public std::logic_error
{
public:
  assert_failure(const char* expr, const char* func, const char* file, int line)
  : std::logic_error(build_message(expr, func, file, line))
  { }

private:
  static std::string build_message(const char* expr, const char* func, const char* file, int line)
  {
    std::stringstream message;
    message << "Assertion failed (" << expr << ") failed at " << func << " (" << file << ':' << line << ")\n";
    return message.str();
  }
};

void assert_fail_abort(const char* expr, const char* func, int line, const char* file) noexcept __attribute__((noreturn));
void assert_fail_throw(const char* expr, const char* func, int line, const char* file);

inline __attribute__((noreturn))
void assert_fail_inline_abort(const char* expr, const char* func, const char* file, int line) noexcept
{
  std::printf("Assertion failed (%s) failed at %s (%s:%d)\n", expr, func, file, line);
  std::terminate();
}

inline
void assert_fail_inline_throw(const char* expr, const char* func, const char* file, int line)
{
  throw assert_failure(expr, func, file, line);
}

#define CPP_ASSERT_FAIL_ABORT ::cpp::assert_fail_abort
#define CPP_ASSERT_FAIL_THROW ::cpp::assert_fail_throw
#define CPP_ASSERT_FAIL_INLINE_ABORT ::cpp::assert_fail_inline_abort
#define CPP_ASSERT_FAIL_INLINE_THROW ::cpp::assert_fail_inline_throw

/// defaults CPP_ASSERT_FAIL to CPP_ASSERT_FAIL_INLINE_ABORT
#ifndef CPP_ASSERT_FAIL
# define CPP_ASSERT_FAIL CPP_ASSERT_FAIL_INLINE_ABORT
#endif

} // namespace cpp

#endif /* CPP_UTILS_ASSERT_H_ */
