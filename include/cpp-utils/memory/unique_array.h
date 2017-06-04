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

#ifndef INCLUDE_CPP_UTILS_MEMORY_UNIQUE_ARRAY_H_
#define INCLUDE_CPP_UTILS_MEMORY_UNIQUE_ARRAY_H_

#include <memory>

#include "../array_view.h"

namespace cpp {

template<typename T, typename Deleter = std::default_delete<T[]>>
class unique_array
{
public:
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using deleter_type = Deleter;

  explicit unique_array()
  : data_()
  { }

  explicit unique_array(pointer ptr, std::size_t size)
  : data_(internal(ptr, size), Deleter())
  { }

  explicit unique_array(pointer ptr, std::size_t size,
    typename std::conditional<std::is_reference<deleter_type>::value, deleter_type, const deleter_type&>::type deleter)
  : data_(internal(ptr, size), deleter)
  { }

  explicit unique_array(pointer ptr, std::size_t size,
    typename std::remove_reference<deleter_type>::type&& deleter)
  : data_(internal(ptr, size), deleter)
  { static_assert(!std::is_reference<deleter_type>::value,
    "rvalue deleter bound to reference"); }

  unique_array(unique_array&& other) noexcept
  : data_(other.release(), std::forward<deleter_type>(other.get_deleter()))
  { }

  unique_array& operator=(unique_array&& other) noexcept
  {
    reset(other.release());
    get_deleter() = std::forward<deleter_type>(other.get_deleter());
    return *this;
  }

  ~unique_array() noexcept
  {
    auto& i = get_internal();
    if (i.ptr != nullptr)
      get_deleter()(i.ptr);
    i = internal();
  }

  iterator begin() { return get_internal().ptr; }
  const_iterator begin() const { return get_internal().ptr; }
  const_iterator cbegin() const { return get_internal().ptr; }

  iterator end() { return get_internal().ptr + get_internal().n; }
  const_iterator end() const { return get_internal().ptr + get_internal().n; }
  const_iterator cend() const { return get_internal().ptr + get_internal().n; }

  pointer data() { return get_internal().ptr; }
  const_pointer data() const { return get_internal().ptr; }

  std::size_t size() const { return get_internal().n; }

  // TODO: range check
  reference operator[](std::size_t n) { return get_internal().ptr[n]; }
  const_reference operator[](std::size_t n) const { return get_internal().ptr[n]; }

  // TODO: range check
  reference at(std::size_t n) { return get_internal().ptr[n]; }
  const_reference at(std::size_t n) const { return get_internal().ptr[n]; }

  bool empty() const { return get_internal().n == 0; }
  explicit operator bool () const { return !empty(); }

  deleter_type& get_deleter() { return std::get<1>(data_); }
  const deleter_type& get_deleter() const { return std::get<1>(data_); }

  array_view<T> release() noexcept
  {
    auto array = get_internal().as_view();
    get_internal() = internal();
    return array;
  }

  void reset(array_view<T> other = array_view<T>()) noexcept
  {
    using std::swap;

    auto newinternal = internal(other);
    swap(get_internal(), newinternal);

    if (newinternal.ptr != nullptr)
      get_deleter()(newinternal.ptr);
  }

  void swap(unique_array& other) noexcept
  {
    using std::swap;
    swap(data_, other.data_);
  }

  unique_array(const unique_array&) = delete;
  unique_array& operator=(const unique_array&) = delete;

private:
  struct internal
  {
    T* ptr = nullptr;
    std::size_t n = 0;

    internal() = default;
    internal(T* ptr_, std::size_t n_) : ptr(ptr_), n(n_) { }
    internal(array_view<T> view) : ptr(view.data()), n(view.size()) { }

    array_view<T> as_view() const { return array_view<T>(ptr, n); }
  };
  std::tuple<internal, deleter_type> data_;

  internal& get_internal() { return std::get<0>(data_); }
  const internal& get_internal() const { return std::get<0>(data_); }
};


template<typename T>
unique_array<T> make_unique_array(std::size_t n)
{
  return unique_array<T>(new T[n], n);
}

} // namespace cpp

#endif /* INCLUDE_CPP_UTILS_MEMORY_UNIQUE_ARRAY_H_ */
