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

#ifndef INCLUDE_CPP_UTILS_COPY_POLICY_H_
#define INCLUDE_CPP_UTILS_COPY_POLICY_H_

#include <type_traits>

namespace cpp {

namespace copy_policy_noadl { // ADL barrier

// low level user interface

template<bool, bool>
struct copy_ctor_policy_base;

// not copy constructable and not move constructable
template<>
struct copy_ctor_policy_base<false, false>
{
  constexpr copy_ctor_policy_base() noexcept = default;
  constexpr copy_ctor_policy_base(const copy_ctor_policy_base&) = delete;
  constexpr copy_ctor_policy_base(copy_ctor_policy_base&&) = delete;
  copy_ctor_policy_base& operator=(const copy_ctor_policy_base&) noexcept = default;
  copy_ctor_policy_base& operator=(copy_ctor_policy_base&&) noexcept = default;
};

// copy constructable and not move constructable
template<>
struct copy_ctor_policy_base<true, false>
{
  constexpr copy_ctor_policy_base() noexcept = default;
  constexpr copy_ctor_policy_base(const copy_ctor_policy_base&) = default;
  constexpr copy_ctor_policy_base(copy_ctor_policy_base&&) = delete;
  copy_ctor_policy_base& operator=(const copy_ctor_policy_base&) noexcept = default;
  copy_ctor_policy_base& operator=(copy_ctor_policy_base&&) noexcept = default;
};

// not copy constructable and move constructable
template<>
struct copy_ctor_policy_base<false, true>
{
  constexpr copy_ctor_policy_base() noexcept = default;
  constexpr copy_ctor_policy_base(const copy_ctor_policy_base&) = delete;
  constexpr copy_ctor_policy_base(copy_ctor_policy_base&&) = default;
  copy_ctor_policy_base& operator=(const copy_ctor_policy_base&) noexcept = default;
  copy_ctor_policy_base& operator=(copy_ctor_policy_base&&) noexcept = default;
};

// copy constructable and move constructable
template<>
struct copy_ctor_policy_base<true, true>
{
  constexpr copy_ctor_policy_base() noexcept = default;
  constexpr copy_ctor_policy_base(const copy_ctor_policy_base&) = default;
  constexpr copy_ctor_policy_base(copy_ctor_policy_base&&) = default;
  copy_ctor_policy_base& operator=(const copy_ctor_policy_base&) noexcept = default;
  copy_ctor_policy_base& operator=(copy_ctor_policy_base&&) noexcept = default;
};

template<bool, bool>
struct copy_assign_policy_base;

// not copy assignable and not move assignable
template<>
struct copy_assign_policy_base<false, false>
{
  constexpr copy_assign_policy_base() noexcept = default;
  constexpr copy_assign_policy_base(const copy_assign_policy_base&) = default;
  constexpr copy_assign_policy_base(copy_assign_policy_base&&) = default;
  copy_assign_policy_base& operator=(const copy_assign_policy_base&) noexcept = delete;
  copy_assign_policy_base& operator=(copy_assign_policy_base&&) noexcept = delete;
};

// copy assignable and not move assignable
template<>
struct copy_assign_policy_base<true, false>
{
  constexpr copy_assign_policy_base() noexcept = default;
  constexpr copy_assign_policy_base(const copy_assign_policy_base&) = default;
  constexpr copy_assign_policy_base(copy_assign_policy_base&&) = default;
  copy_assign_policy_base& operator=(const copy_assign_policy_base&) noexcept = default;
  copy_assign_policy_base& operator=(copy_assign_policy_base&&) noexcept = delete;
};

// not copy assignable and move assignable
template<>
struct copy_assign_policy_base<false, true>
{
  constexpr copy_assign_policy_base() noexcept = default;
  constexpr copy_assign_policy_base(const copy_assign_policy_base&) = default;
  constexpr copy_assign_policy_base(copy_assign_policy_base&&) = default;
  copy_assign_policy_base& operator=(const copy_assign_policy_base&) noexcept = delete;
  copy_assign_policy_base& operator=(copy_assign_policy_base&&) noexcept = default;
};

// copy assignable and move assignable
template<>
struct copy_assign_policy_base<true, true>
{
  constexpr copy_assign_policy_base() noexcept = default;
  constexpr copy_assign_policy_base(const copy_assign_policy_base&) = default;
  constexpr copy_assign_policy_base(copy_assign_policy_base&&) = default;
  copy_assign_policy_base& operator=(const copy_assign_policy_base&) noexcept = default;
  copy_assign_policy_base& operator=(copy_assign_policy_base&&) noexcept = default;
};

// high level user interface

// use copy policy of other class

/// \brief use copy/move constructible capability of \p T
template<typename T>
struct use_copy_ctor_policy_of :
  copy_ctor_policy_base<
    std::is_copy_constructible<T>::value, std::is_move_constructible<T>::value
  >
{ };

/// \brief use copy/move assignable capability of \p T
template<typename T>
struct use_copy_assign_policy_of :
  copy_assign_policy_base<
    std::is_copy_assignable<T>::value, std::is_move_assignable<T>::value
  >
{ };

/// \brief use copy/move capability of \p T
template<typename T>
struct use_copy_policy_of :
  use_copy_ctor_policy_of<T>, use_copy_assign_policy_of<T>
{ };

// copy policy from template

struct noncopyable
 :  copy_ctor_policy_base<false, false>, copy_assign_policy_base<false, false>
{ };

struct movable
 :  copy_ctor_policy_base<false, true>, copy_assign_policy_base<false, true>
{ };

} // namespace copy_policy_noadl

using namespace copy_policy_noadl; // ADL barrier

} // namespace cpp

#endif /* INCLUDE_CPP_UTILS_COPY_POLICY_H_ */
