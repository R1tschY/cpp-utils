#ifndef INCLUDE_CPP_UTILS_SCOPE_H_
#define INCLUDE_CPP_UTILS_SCOPE_H_

#include <utility>
#include <exception>

#include "preprocessor.h"
#include "bits/uncaught_exceptions.h"

namespace cpp {

/// \brief a scope guard
/// \sa https://github.com/facebook/folly
template<typename Func>
class scope_guard
{
public:
  explicit scope_guard(const Func& func) : func_(func) { }
  explicit scope_guard(Func&& func) : func_(std::move(func)) { }

  scope_guard(scope_guard&& other)
  noexcept(std::is_nothrow_move_constructible<Func>::value)
  : func_(std::move_if_noexcept(other.func_)), active_(other.active_)
  {
    other.active_ = false;
  }

  /// execute final action
  ~scope_guard() { if (active_) func_(); }

  // non-copyable
  scope_guard(const scope_guard&) = delete;
  scope_guard& operator=(const scope_guard&) = delete;

private:
  Func func_;
  bool active_ = true;
};

template<typename Func>
scope_guard<Func> make_guard(Func&& func)
{
  return scope_guard<Func>(std::forward<Func>(func));
}

template<typename Func>
scope_guard<Func> finally(Func&& func)
{
  return make_guard(std::forward<Func>(func));
}

namespace detail {

/// \brief helper class for scope_exit
///
/// from Andrei Alexandrescu's talk at CppCpn 2015 'Declarative Control Flow'
enum class scope_guard_onexit { };
enum class scope_guard_onfail { };
enum class scope_guard_onsuccess { };

/// \brief notify if a new exception is thrown in this scope
///
/// \details
/// from Andrei Alexandrescu's talk at CppCon 2015 'Declarative Control Flow'
/// and https://github.com/panaseleus/stack_unwinding
class unwinding_indicator
{
public:
  unwinding_indicator()
    : exception_count_(uncaught_exceptions())
  { }

  bool unwinding() const noexcept
  {
    return uncaught_exceptions() > exception_count_;
  }

private:
  unsigned exception_count_;
};

/// \brief execute function if (no) exception in scope is thrown
///
/// from Andrei Alexandrescu's talk at CppCon 2015 'Declarative Control Flow'
template<typename FunctionType, bool executeOnException>
class scope_guard_ex
{
public:
  explicit scope_guard_ex(const FunctionType& fn)
  : func_(fn)
  { }

  explicit scope_guard_ex(FunctionType&& fn)
  : func_(std::move(fn))
  { }

  ~scope_guard_ex() noexcept(executeOnException)
  {
    if (ind_.unwinding() == executeOnException)
    {
      func_();
    }
  }

private:
  FunctionType func_;
  unwinding_indicator ind_;
};

/// \brief helper for scope(exit)
///
/// from Andrei Alexandrescu's talk at CppCpn 2015 'Declarative Control Flow'
template<typename Func> inline
scope_guard<Func> operator+(scope_guard_onexit, Func&& fn)
{
  return scope_guard<Func>(std::forward<Func>(fn));
}

/// \brief helper for scope(fail)
///
/// from Andrei Alexandrescu's talk at CppCpn 2015 'Declarative Control Flow'
template<typename Func> inline
scope_guard_ex<Func, true> operator+(scope_guard_onfail, Func&& fn)
{
  return scope_guard_ex<Func, true>(std::forward<Func>(fn));
}

/// \brief helper for scope(success)
///
/// from Andrei Alexandrescu's talk at CppCpn 2015 'Declarative Control Flow'
template<typename Func> inline
scope_guard_ex<Func, false> operator+(scope_guard_onsuccess, Func&& fn)
{
  return scope_guard_ex<Func, false>(std::forward<Func>(fn));
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
    = ::cpp::detail::scope_guard_onexit() + [&]()

#define scope_fail \
  auto CPP_UNIQUE_NAME(SCOPE_FAIL_STATE) \
    = ::cpp::detail::scope_guard_onfail() + [&]() noexcept

#define scope_success \
  auto CPP_UNIQUE_NAME(SCOPE_SUCCESS_STATE) \
    = ::cpp::detail::scope_guard_onsuccess() + [&]()


template<typename Func1, typename Func2>
class scope_transaction
{
public:
  explicit scope_transaction(const Func1& success_fn, const Func2& failure_fn)
  : success_fn_(success_fn), failure_fn_(failure_fn)
  { }

  explicit scope_transaction(Func1&& success_fn, Func2&& failure_fn)
  : success_fn_(std::move(success_fn)), failure_fn_(std::move(failure_fn))
  { }

  ~scope_transaction() noexcept(true)
  {
    if (ind_.unwinding())
    {
      failure_fn_();
    }
    else
    {
      success_fn_();
    }
  }

private:
  Func1 success_fn_;
  Func2 failure_fn_;
  detail::unwinding_indicator ind_;
};


template<typename Func1, typename Func2>
scope_transaction<Func1, Func2> make_transaction(
  Func1&& success,
  Func2&& failure
)
{
  return scope_transaction<Func1, Func2>(
    std::forward<Func1>(success), std::forward<Func2>(failure)
  );
}

}  // namespace cpp

#endif /* INCLUDE_CPP_UTILS_SCOPE_H_ */
