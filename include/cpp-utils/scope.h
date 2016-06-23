#ifndef INCLUDE_CPP_UTILS_SCOPE_H_
#define INCLUDE_CPP_UTILS_SCOPE_H_

#include <utility>
#include <exception>

#include "preprocessor.h"

namespace cpp {

namespace detail {

/// \brief helper class for scope_exit
///
/// from Andrei Alexandrescu's talk at CppCpn 2015 'Declarative Control Flow'
enum class ScopeGuardOnExit { };

enum class ScopeGuardOnFail { };
enum class ScopeGuardOnSuccess { };

/// \brief helper for scope_exit
///
/// from Andrei Alexandrescu's talk at CppCpn 2015 'Declarative Control Flow'
template<typename Func> inline
Guide::Final_act<Func> operator+(ScopeGuardOnExit, Func&& fn)
{
  return Guide::Final_act<Func>(std::forward<Func>(fn));
}

int uncaught_exceptions() { return std::uncaught_exception()?1:0; }
// int uncaught_exceptions() { return std::uncaught_exceptions(); }

/// \brief notify if a new exception is thrown in this scope
///
/// from Andrei Alexandrescu's talk at CppCpn 2015 'Declarative Control Flow'
class UncaughtExceptionCounter
{
  int getUncaughtExceptionCount() const noexcept { return exceptionCount_; }
  int exceptionCount_;
public:
  UncaughtExceptionCounter()
    : exceptionCount_(uncaught_exceptions())
  { }

  bool newUncaughtException() const noexcept
  {
    return uncaught_exceptions() > exceptionCount_;
  }
};

/// \brief execute function if (no) exception in scope is thrown
///
/// from Andrei Alexandrescu's talk at CppCpn 2015 'Declarative Control Flow'
template<typename FunctionType, bool executeOnException>
class ScopeGuardForNewException
{
  FunctionType function_;
  UncaughtExceptionCounter ec_;
public:
  explicit ScopeGuardForNewException(const FunctionType& fn)
  : function_(fn)
  { }

  explicit ScopeGuardForNewException(FunctionType&& fn)
  : function_(std::move(fn))
  { }

  ~ScopeGuardForNewException() noexcept(executeOnException)
  {
    if (executeOnException == ec_.newUncaughtException())
    {
      function_();
    }
  }
};

template<typename Func> inline
ScopeGuardForNewException<Func, true> operator+(ScopeGuardOnFail, Func&& fn)
{
  return { std::forward<Func>(fn) };
}

template<typename Func> inline
ScopeGuardForNewException<Func, false> operator+(ScopeGuardOnSuccess, Func&& fn)
{
  return { std::forward<Func>(fn) };
}

}  // namespace detail

/// \brief execute something at the end of this scope
///
/// \code
/// void f()
/// {
///   void* p = malloc(42);
///   scope_exit { if (p) free(p); }
///   // ...
/// }
/// \endcode
///
/// from Andrei Alexandrescu's talk at CppCon 2015 'Declarative Control Flow'
#define scope_exit \
  auto CPP_UNIQUE_NAME(SCOPE_EXIT_STATE) \
  = ::cpp::detail::ScopeGuardOnExit() + [&]()

#define scope_fail \
  auto CPP_UNIQUE_NAME(SCOPE_FAIL_STATE) \
  = ::cpp::detail::ScopeGuardOnFail() + [&]() noexcept

#define scope_success \
  auto CPP_UNIQUE_NAME(SCOPE_SUCCESS_STATE) \
  = ::cpp::detail::ScopeGuardOnSuccess() + [&]()

}  // namespace cpp

#endif /* INCLUDE_CPP_UTILS_SCOPE_H_ */
