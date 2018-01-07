///
/// Copyright (c) 2017 R1tschY
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

#include <tuple>
#include <functional>

// old

#define lambda_(...) ([&](auto& _) { return (__VA_ARGS__); })
#define lambda1(...) ([&](auto& _1) { return (__VA_ARGS__); })
#define lambda2(...) ([&](auto& _1, auto& _2) { return (__VA_ARGS__); })

// new

namespace cpp {
namespace lambda {

// param

template<std::size_t N>
struct _param_
{
  constexpr _param_() = default;

  static constexpr auto n = N;

  template<typename...Args>
  auto operator()(Args&&...args) const
  {
    return std::get<N>(std::forward_as_tuple(std::forward<Args>(args)...));
  }
};

constexpr auto _a = _param_<0>();
constexpr auto _b = _param_<1>();

// operators

template<typename BinOp, typename F1, typename F2>
struct _binop_ : private std::tuple<BinOp, F1, F2>
{
  constexpr _binop_(F1&& f1, F2&& f2)
  : base(
      BinOp(),
      std::forward<F1>(f1),
      std::forward<F2>(f2)
    )
  { }

  template<typename...Args>
  auto operator()(Args&&...args) const
  {
    return get<0>()(
      get<1>()(std::forward<Args>(args)...),
      get<2>()(std::forward<Args>(args)...)
    );
  }

  template<typename...Args>
  auto operator()(Args&&...args)
  {
    return get<0>()(
      get<1>()(std::forward<Args>(args)...),
      get<2>()(std::forward<Args>(args)...)
    );
  }

private:
  using base = std::tuple<BinOp, F1, F2>;

  template<std::size_t N>
  auto get()
  {
    return std::get<N>(*static_cast<base*>(this));
  }
};

template<typename InplaceOp, typename F1, typename F2>
struct _inplaceop_ : private std::tuple<InplaceOp, F1, F2>
{
  constexpr _inplaceop_(F1&& f1, F2&& f2)
  : base(
      InplaceOp(),
      std::forward<F1>(f1),
      std::forward<F2>(f2)
    )
  { }

  template<typename...Args>
  auto operator()(Args&&...args) const
  {
    return get<0>()(
      get<1>()(std::forward<Args>(args)...),
      get<2>()(std::forward<Args>(args)...)
    );
  }

  template<typename...Args>
  auto operator()(Args&&...args)
  {
    return get<0>()(
      get<1>()(std::forward<Args>(args)...),
      get<2>()(std::forward<Args>(args)...)
    );
  }

private:
  using base = std::tuple<InplaceOp, F1, F2>;

  template<std::size_t N>
  auto get()
  {
    return std::get<N>(*static_cast<base*>(this));
  }
};

template<typename T = void>
struct iadd
{
  constexpr
  T& operator()(T& rhs, const T& lhs) const
  {
    return rhs += lhs;
  }
};

template<>
struct iadd<void>
{
  template <typename Lhs, typename Rhs>
  constexpr auto
  operator()(Lhs&& lhs, Rhs&& rhs) const
  { return std::forward<Lhs>(lhs) += std::forward<Rhs>(rhs); }
};

template<typename F1, typename F2>
using _add_ = _binop_<const std::plus<>, F1, F2>;

template<typename F1, typename F2>
constexpr auto _add(F1&& f1, F2&& f2)
{
  return _add_<F1, F2>(std::forward<F1>(f1), std::forward<F2>(f2));
}

template<typename F1, typename F2>
using _iadd_ = _binop_<const iadd<>, F1, F2>;

template<typename F1, typename F2>
constexpr auto _iadd(F1&& f1, F2&& f2)
{
  return _iadd_<F1, F2>(std::forward<F1>(f1), std::forward<F2>(f2));
}

template<typename F1, typename F2>
using _less_ = _binop_<const std::less<>, F1, F2>;

template<typename F1, typename F2>
constexpr auto _less(F1&& f1, F2&& f2)
{
  return _less_<F1, F2>(std::forward<F1>(f1), std::forward<F2>(f2));
}

// const

template<typename T>
struct _var_ : private std::tuple<T>
{
  _var_(T&& t) : std::tuple<T>(std::forward<T>(t)) { }

  template<typename...Args>
  T& operator()(Args&&...args)
  {
    return std::get<0>(*static_cast<std::tuple<T>*>(this));
  }
};

template<typename T>
constexpr auto _var(T&& t)
{
  return _var_<T>(std::forward<T>(t));
}

template<typename T>
struct _varref_ : private std::tuple<T&>
{
  _varref_(T& t) : std::tuple<T&>(t) { }

  template<typename...Args>
  T& operator()(Args&&...args)
  {
    return std::get<0>(*static_cast<std::tuple<T&>*>(this));
  }
};

template<typename T>
constexpr auto _varref(T& t)
{
  return _varref_<T>(t);
}

template<typename T>
struct _val_ : private std::tuple<const T>
{
  _val_(T&& t) : std::tuple<const T>(std::forward<T>(t)) { }

  template<typename...Args>
  const T& operator()(Args&&...args) const
  {
    return std::get<0>(*static_cast<std::tuple<const T>*>(this));
  }
};

template<typename T>
constexpr auto _val(T&& t)
{
  return _val_<T>(std::forward<T>(t));
}

template<typename T>
struct _valref_ : private std::tuple<const T&>
{
  _valref_(const T& t) : std::tuple<const T&>(t) { }

  template<typename...Args>
  const T& operator()(Args&&...args) const
  {
    return std::get<0>(*static_cast<std::tuple<const T&>*>(this));
  }
};

template<typename T>
constexpr auto _valref(const T& t)
{
  return _valref_<T>(t);
}

// object access

template<typename T, T Field, typename Func>
struct _field_;

template<typename A, typename T, T A::*Field, typename Func>
struct _field_<T A::*, Field, Func> : private std::tuple<Func>
{
  _field_(Func&& func)
  : std::tuple<Func>(std::forward<Func>(func))
  { }

  template<typename...Args>
  T operator()(Args&&...args) const
  {
    auto& func = std::get<0>(*static_cast<const std::tuple<Func>*>(this));
    return func(std::forward<Args>(args)...).*Field;
  }
};

template<typename T, T Field, typename Func>
constexpr auto _field(Func&& func)
{
  return _field_<T, Field, Func>(std::forward<Func>(func));
}

#define _FIELD(field, ...) ::cpp::lambda::_field<decltype(field), field>(__VA_ARGS__)

}  // namespace lambda
} // namespace cpp


