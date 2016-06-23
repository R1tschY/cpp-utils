/// \file iterator_range.h

#ifndef INCLUDE_CPP_UTILS_ITERATOR_RANGE_H_
#define INCLUDE_CPP_UTILS_ITERATOR_RANGE_H_

namespace cpp {

/// \brief a range from two iterator
///
/// \details use make_range to create a range
template<typename T1, typename T2 = T1>
class iterator_range
{
public:
  explicit iterator_range(T1 first, T2 last)
    : begin_(std::move(first)), end_(std::move(last))
  { }

  T1 begin() const { return begin_; }
  T2 end() const { return end_; }

  bool operator==(const iterator_range& other)
  {
    return begin_ == other.begin_ && end_ == other.end_;
  }
  bool operator!=(const iterator_range& other) { return !(*this == other); }

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
