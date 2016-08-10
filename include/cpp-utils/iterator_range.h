/// \file iterator_range.h

#ifndef INCLUDE_CPP_UTILS_ITERATOR_RANGE_H_
#define INCLUDE_CPP_UTILS_ITERATOR_RANGE_H_

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <utility>

#include "assert.h"

namespace cpp {

struct unsafe_tag { };
constexpr static unsafe_tag unsafe{};

/// \brief a range from two iterator
///
/// \details use make_range to create a range
template<typename T1, typename T2 = T1>
class iterator_range
{
public:
  using traits = std::iterator_traits<T1>;
  using difference_type   = typename traits::difference_type;
  using value_type        = typename traits::value_type;
  using pointer           = typename traits::pointer;
  using reference         = typename traits::reference;
  using iterator_category = typename traits::iterator_category;

  explicit iterator_range(T1 first, T2 last = T2())
    : begin_(std::move(first)), end_(std::move(last))
  {
    // TODO: for rai:
    //cpp_assert(first >= last);
  }

  T1 begin() const { return begin_; }
  T2 end() const { return end_; }

  constexpr bool empty() const { return begin_ == end_; }
  constexpr explicit operator bool () const { return empty(); }

  /// \bug create cpp:distance for T1 != T2
  constexpr std::size_t size() const { return std::distance(begin_, end_); }
  constexpr std::size_t length() const { return size(); }

  bool operator==(const iterator_range& other)
  {
    return begin_ == other.begin_ && end_ == other.end_;
  }
  bool operator!=(const iterator_range& other) { return !(*this == other); }

  void pop_front() { if (!empty()) ++begin_; }
  void pop_front(unsafe_tag) { cpp_assert(!empty()); ++begin_; }

  void pop_front(std::size_t n, std::random_access_iterator_tag)
  {
    std::advance(begin_, std::min(size(), n));
  }

  void pop_front(std::size_t n, unsafe_tag)
  {
    cpp_assert(n <= size());
    std::advance(begin_, n);
  }

  /// \todo fast version for ra-iterators
  void pop_front(std::size_t n)
  {
    while (n > 0 && !empty())
    {
      --n;
      ++begin_;
    }
  }

  void pop_back() { if (!empty()) --end_; }
  void pop_back(unsafe_tag) { cpp_assert(!empty()); --end_; }

  void pop_back(std::size_t n, std::random_access_iterator_tag)
  {
    std::advance(end_, -std::min(size(), n));
  }
  void pop_back(std::size_t n, unsafe_tag)
  {
    cpp_assert(n <= size());
    std::advance(end_, -n);
  }

  /// \todo fast version for ra-iterators
  /// \pre T1 == T2, T1 == bidirectional_iterator
  void pop_back(std::size_t n)
  {
    while (n > 0 && !empty())
    {
      --n;
      --end_;
    }
  }

  /// \pre T1 == T2
  void slice(std::size_t pos, std::size_t n, std::random_access_iterator_tag)
  {
    pop_front(pos);

    end_ = std::advance(begin_, std::min(size(), n));
  }

  /// \pre T1 == T2
  void slice(std::size_t pos, std::size_t n)
  {
    pop_front(pos);

    T1 new_end = begin_;
    while (n > 0 && new_end != end_)
    {
      --n;
      ++new_end;
    }
  }

  auto operator[](std::size_t index) -> decltype(*begin())
  {
    cpp_assert(index < size());
    return *std::advance(begin_, index);
  }

  auto operator[](std::size_t index) const -> decltype(*begin())
  {
    cpp_assert(index < size());
    return *std::advance(begin_, index);
  }

  auto at(std::size_t index) -> decltype(*begin())
  {
    cpp_assert(index < size());
    return *std::advance(begin_, index);
  }

  auto at(std::size_t index) const -> decltype(*begin())
  {
    cpp_assert(index < size());
    return *std::advance(begin_, index);
  }

  /// \pre T1 == T2, T1 == bidirectional_iterator
  auto back(std::size_t index) -> decltype(*begin())
  {
    cpp_assert(index < size());
    return *std::advance(end_, -index);
  }

  /// \pre T1 == T2, T1 == bidirectional_iterator
  auto back(std::size_t index) const -> decltype(*begin())
  {
    cpp_assert(index < size());
    return *std::advance(end_, -index);
  }

private:
  T1 begin_;
  T2 end_;
};

/// \brief create a iterator_range from two iterators
template<typename T1, typename T2>
iterator_range<T1, T2> make_range(T1 iter1, T2 iter2)
{
  return iterator_range<T1, T2>(std::move(iter1), std::move(iter2));
}

/// \brief create a iterator_range from a pair of iterators
template<typename T1, typename T2>
iterator_range<T1, T2> make_range(std::pair<T1, T2> iters)
{
  return iterator_range<T1, T2>(std::move(iters.first), std::move(iters.second));
}

/// \brief create a iterator_range from a range
/// \details uses std::begin and std::end to get the iterators of the range
template<typename Range>
auto make_range(Range& range) -> iterator_range<decltype(std::begin(range)), decltype(std::end(range))>
{
  return iterator_range<
    decltype(std::begin(range)), decltype(std::end(range))
    > (std::begin(range), std::end(range));
}


}  // namespace cpp

#endif /* INCLUDE_CPP_UTILS_ITERATOR_RANGE_H_ */
