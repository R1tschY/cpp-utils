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

#ifndef LIBS_C___INCLUDE_CPP_UTILS_COMPILER_COMPILER_H_
#define LIBS_C___INCLUDE_CPP_UTILS_COMPILER_COMPILER_H_

#ifdef __clang__

# define CPP_CLANG_VERSION_FUNC(major, minor) ((major) << 8 | (minor))
# define CPP_CLANG CPP_CLANG_VERSION_HEX_FUNC(__clang_major__, __clang_minor__)

# define CPP_CLANG_VERSION_CHECK(major, minor) \
  (CPP_CLANG >= CPP_CLANG_VERSION_FUNC(major, minor))


#else
#define CPP_CLANG_VERSION_CHECK(major, minor) 0
#endif

#ifdef __GNUC__

# define CPP_GCC_VERSION_FUNC(major, minor, patch) ((major) << 16 | (minor) << 8 | (patch))

# define CPP_GCC_COMPATIBLE CPP_GCC_VERSION_FUNC(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
# ifndef __clang__
#  define CPP_GCC CPP_GCC_VERSION_FUNC(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#  define CPP_GCC_VERSION_CHECK(major, minor, patch) \
     (CPP_GCC >= CPP_CLANG_VERSION_FUNC(major, minor))
# endif

#else
#define CPP_GCC_VERSION_CHECK(major, minor, patch) 0
#endif

#ifdef _MSC_VER

# define CPP_MSC _MSC_VER
# define CPP_MSC_VERSION_CHECK(version) (CPP_MSC >= version)

#else
#define CPP_MSC_VERSION_CHECK(version) 0
#endif

#define CPP_FEATURE_CHECK_I(x, version) (defined(x) && x >= version)
#define CPP_FEATURE_CHECK(x, version) CPP_FEATURE_CHECK_I(x, version)

#endif /* LIBS_C___INCLUDE_CPP_UTILS_COMPILER_COMPILER_H_ */
