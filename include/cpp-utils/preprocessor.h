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

#ifndef BLOCKS_R1TSCHY_CPP_UTILS_INCLUDE_PREPROCESSOR_H_
#define BLOCKS_R1TSCHY_CPP_UTILS_INCLUDE_PREPROCESSOR_H_

/// \defgroup Macros macro helper
/// \{

#ifndef __DOXYGEN__

// interna

#define CPP_NARGS(args...)  _CPP_NARGS_I_(,##args,_CPP_RSEQ_N())
#define _CPP_NARGS_I_(...) _CPP_ARGS_N(__VA_ARGS__)
#define _CPP_ARGS_N( \
      _0, _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define _CPP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

#define _CPP_VFUNC_(name, n) name##n
#define _CPP_VFUNC(name, n) _CPP_VFUNC_(name, n)

#define _CPP_CONCAT1(a) a
#define _CPP_CONCAT2(a,b) a##b
#define _CPP_CONCAT3(a,b,c) a##b##c
#define _CPP_CONCAT4(a,b,c,d) a##b##c##d
#define _CPP_CONCAT5(a,b,c,d,e) a##b##c##d##e
#define _CPP_CONCAT6(a,b,c,d,e,f) a##b##c##d##e##f

#define _CPP_CONCAT_1(a) a
#define _CPP_CONCAT_2(a,b) a##,##b
#define _CPP_CONCAT_3(a,b,c) a##,##b##,##c
#define _CPP_CONCAT_4(a,b,c,d) a##,##b##,##c##,##d
#define _CPP_CONCAT_5(a,b,c,d,e) a##,##b##,##c##,##d##,##e
#define _CPP_CONCAT_6(a,b,c,d,e,f) a##,##b##,##c##,##d##,##e##,##f
#define _CPP_CONCAT_(...) CPP_VFUNC(_CPP_CONCAT_, __VA_ARGS__)

#define _CPP_CONCAT_FUNC(n) _CPP_CONCAT_FUNC_(n)
#define _CPP_CONCAT_FUNC_(n) _CPP_CONCAT ## n

#define _CPP_STRINGIFY_(x) #x
#define _CPP_STRINGIFY(x) _CPP_STRINGIFY_(x)

#else // __DOXYGEN__

///  \brief give number of arguments
///
/// copied from: https://groups.google.com/group/comp.std.c/browse_thread/thread/77ee8c8f92e4a3fb/346fc464319b1ee5?pli=1
///
/// \code
/// int x = CPP_NARGS(a,b,c,d,e,f); // after preprocessing: int x = 6;
/// \endcode
///
/// \pre not more than 64 arguments
/// \bug in GCC a call without arguments results in constant 1
#define CPP_NARGS(...)

#endif // __DOXYGEN__

/// \brief call function dependent on the number of arguments
///
/// The `name` parameter is the basename on which the number of arguments
/// is appended. The composed function name will be called.
///
/// This functionality is useful when used with functions in C or macro functions,
/// because they cannot have overloads with a variable number of arguments
/// unlike the C++ functions.
///
/// To make use of this macro the functions have to be declared, e.x. a SUM macro function:
/// \code
/// #define SUM1(x) (x)
/// #define SUM2(x,y) ((x) + (y))
/// #define SUM3(x,y,z) ((x) + (y) + (z))
/// #define SUM(...) CPP_VFUNC(SUM, __VA_ARGS__)
/// \endcode
///
/// A simple call to the created macro function with maximal three arguments
/// is now possible:
/// \code
/// int S = SUM(x, 5, 42); // uses SUM3
/// \endcode
///
/// This is also possible with C functions:
/// \code
/// int sum0() { return 0; }
/// int sum1(int x) { return x; }
/// int sum2(int x, int y) { return x + y; }
/// int sum3(int x, int y, int z) { return x + y + z; }
/// #define sum(...) CPP_VFUNC(sum, __VA_ARGS__)
///
/// int s = sum(x, 5, 42); // uses sum3
/// \endcode
///
/// \pre maximum 64 arguments
/// \bug a call without arguments will not work
/// \sa CPP_NARGS
#define CPP_VFUNC(name, ...) _CPP_VFUNC(name, CPP_NARGS(__VA_ARGS__)) (__VA_ARGS__)

/// \brief combine arguments to new identifier
/// \code
/// #define GET_PIN_ON_PORT(port, bit) (CPP_CONCAT(PORT, port) & CPP_CONCAT(P, port, bit))
/// if (GET_PIN_ON_PORT(B, 1)) { // after preprocessing: PORTB & PB1
///   // ...
/// }
/// \endcode
///
/// \pre Maximal 6 Argumente können angegeben werden.
#define CPP_CONCAT(...) CPP_VFUNC(_CPP_CONCAT, __VA_ARGS__)

/// \brief convert argument to a string literal
///
/// `CPP_STRINGIFY(123)` will be `"123"`
#define CPP_STRINGIFY(x) _CPP_STRINGIFY(x)

/// \brief convert argument to a wide string literal
///
/// `CPP_WSTRINGIFY(123)` will be `L"123"`
#define CPP_WSTRINGIFY(x) CPP_CONCAT(L,_CPP_STRINGIFY(x))

/// \brief convert normal string literal to a wide string literal
///
/// `CPP_TO_WIDESTRING("123")` will be `L"123"`
#define CPP_TO_WIDESTRING(x) CPP_CONCAT(L,x)

////////////////////////////////////////////////////////////////////////////////
// Macro utils

/// \brief empty expression
///
/// example:
/// \code
/// #if OPTION == 42
/// # define my_function() printf("%d", 42)
/// #else
/// # define my_function() CPP_NOOP
/// #endif
/// \endcode
#define CPP_NOOP static_cast<void>(0)

/// \brief Beginning a macro with more than one statement
///
/// You can use this macro in conjunction with CPP_MACRO_END to build
/// macros, that consists of more than one statement.
/// If not used the multi-statement macro can have unexpected results, e.x. when
/// used in a if-statement without brackets.
///
/// example:
/// \code
/// #define PRINT_INT_ARRAY(c) CPP_MACRO_BEGIN \​
///                      for (size_t i = 0; i < sizeof(c)/sizeof(c[0]); i++) { \​
///                         printf("%d ", c[i]); \​
///                      } CPP_MACRO_END
/// \endcode
/// \sa CPP_MACRO_END
#define CPP_MACRO_BEGIN do {

/// \brief End of a macro with more than one statement
/// \sa CPP_MACRO_BEGIN
#define CPP_MACRO_END } while (0)

/// \brief mark a unused variable
///
/// use it to shut the compiler up talking about unused variables
#define CPP_UNUSED(x) static_cast<void>(x)

/// \brief create a unique identifier name
///
/// the generated name with \p prefix will be unique in this source file
#define CPP_UNIQUE_NAME(prefix) _CPP_CONCAT2(prefix, __COUNTER__)

#ifdef __DOXYGEN__
/// \brief Start of a C-API definition
/// \sa CPP_C_API_END
# define CPP_C_API_BEGIN extern "C" {

/// \brief End of a C-API definition
/// \sa CPP_C_API_BEGIN
# define CPP_C_API_END }
#else
# ifdef __cplusplus
#  define CPP_C_API_BEGIN extern "C" {
#  define CPP_C_API_END }
# else
#  define CPP_C_API_BEGIN
#  define CPP_C_API_END
# endif
#endif

/// \brief defines function, that is called with the start of the program
///
/// Use the function to initialize global variables:
/// \code
/// int global_vector[32];
/// int global_int;
///
/// CPP_INITIALIZATION {
///   // compute square numbers
///   for (size_t i = 0; i < cpp:length(global_vector); i++) {
///     global_vector[i] = i*i;
///   }
///
///   // compute the sum of all square numbers until 31
///   global_int = global_vector[0];
///   for (size_t i = 1; i < 31; i++) {
///     global_int += global_vector[i];
///   }
/// }
/// \endcode
///
/// The code is called before `main` when also global C++ class instances are
/// initailizied. The order in that the code is called is undefined. So don't
/// rely on may not initialized global variables (use the singleton pattern
/// for global variables to guarantee that they are initialized before use).
///
/// \code
/// struct RegisterEntry { };
/// class Register
/// {
/// public:
///   void add(RegisterEntry* x) { register_.push_back(x); }
///
///   static Register& get();
///
/// private:
///   Register() { }
///   std::vector<RegisterEntry> register_;
/// };
///
/// Register& Register::get()
/// {
///   static Register instance;
///   return instance;
/// }
///
/// RegisterEntry entry;
/// CPP_INITIALIZATION {
///   Register::get().addAnswer(&entry);
/// }
/// \endcode
///
/// More than one definition in one source file is allowed:
/// \code
/// RegisterEntry entry1;
/// CPP_INITIALIZATION {
///   Register::get().addAnswer(&entry1);
/// }
///
/// // ...
///
/// RegisterEntry entry2;
/// CPP_INITIALIZATION {
///   Register::get().addAnswer(&entry2);
/// }
/// \endcode
/// \sa CPP_FINALIZATION
#define CPP_INITIALIZATION \
  static __attribute__((constructor)) void CPP_UNIQUE_NAME(_CPP_INITIALIZATION_)()


/// \brief defines function, that is called at the exit of the program
///
/// The function is called after `main` exists at the time when all global
/// variables are destructed. The order of execution of CPP_FINALIZATION code blocks
/// is undefined.
///
/// \warning Don't use global variables in the CPP_FINALIZATION code block, because they are maybe already
/// destructed.
///
/// \sa CPP_INITIALIZATION
#define CPP_FINALIZATION \
  static __attribute__((destructor)) void CPP_UNIQUE_NAME(_CPP_FINALIZATION_)()

/// \}

#endif /* BLOCKS_R1TSCHY_CPP_UTILS_INCLUDE_PREPROCESSOR_H_ */
