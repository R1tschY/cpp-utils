#ifndef INCLUDE_CPP_UTILS_ALGORITHM_CONTAINER_H_
#define INCLUDE_CPP_UTILS_ALGORITHM_CONTAINER_H_

#include <algorithm>

#include "../meta/void.h"
#include "../meta/require.h"
#include "length.h"

namespace cpp {

// has_reserve

template<typename, typename = void>
struct has_reserve : std::false_type { };

template<typename T>
struct has_reserve<T, void_t< decltype(std::declval<T>().reserve()) > >
  : std::true_type
{ };

// reserve

template<typename Container, FUNC_REQUIRES(!has_reserve<Container>::value)>
void reserve(Container& c, std::size_t size) { }

template<typename Container, FUNC_REQUIRES(has_reserve<Container>::value)>
void reserve(Container& c, std::size_t size)
{
  c.reserve(size);
}

/// \brief remove duplicates in container
///
/// \details container gets sorted before duplicates are removed.
template<typename Container>
void deduplicate(Container& container)
{
  auto first = container.begin();
  auto last = container.end();

  std::sort(first, last);
  container.erase(std::unique(first, last), last);
}

/// \brief add copy of elements of \p rhs to \p lhs
/// \details append all elements of rhs to lhs by copying
template<typename ContainerLhs, typename ContainerRhs>
void append(ContainerLhs& lhs, const ContainerRhs& rhs)
{
  lhs.insert(lhs.end(), rhs.begin(), rhs.end());
}

/// \brief add elements of \p rhs to \p lhs
/// \details append all elements of rhs to lhs by moving and clear rhs
/// \todo use move_iterator and insert()
template<typename ContainerLhs, typename ContainerRhs>
void merge(ContainerLhs& lhs, ContainerRhs& rhs)
{
  reserve(lhs, length(lhs) + length(rhs));
  std::move(rhs.begin(), rhs.end(), std::back_inserter(lhs));
  rhs.clear();
}

/// \brief copy elements of \p rhs to \p lhs
template<typename ContainerLhs, typename ContainerRhs>
void assign(ContainerLhs& lhs, const ContainerRhs& rhs)
{
  lhs.assign(rhs.begin(), rhs.end());
}

/// \brief transform elements of \p lhs and store to \p rhs
template<typename ContainerLhs, typename ContainerRhs, typename Func>
void transform(const ContainerLhs& lhs, ContainerRhs& rhs, Func&& func)
{
  //reserve(rhs, length(rhs) + length(lhs));
  std::transform(std::begin(lhs), std::end(lhs),
    std::back_inserter(rhs), std::move(func));
}

/// \brief std::sort for ranges
template<typename Range>
void sort(Range& r)
{
  std::sort(std::begin(r), std::end(r));
}

/// \brief std::for_each for ranges
template<typename Range1, typename Func>
void for_each(Range1& r1, Func&& func)
{
  auto cur = std::begin(r1);
  const auto end = std::end(r1);
  for (; cur != end; ++cur)
    func(*cur);
}
template<typename Range1, typename Func>
void for_each(Range1&& r1, Func&& func)
{
  auto cur = std::begin(r1);
  const auto end = std::end(r1);
  for (; cur != end; ++cur)
    func(*cur);
}

/// \brief std::all_of for ranges
template<typename Range1, typename Func>
bool all_of(const Range1& r1, Func&& func)
{
  return std::all_of(std::begin(r1), std::end(r1), std::move(func));
}

/// \brief create std::initializer_list from brace-enclosed list
template<typename T>
std::initializer_list<T> make_list(std::initializer_list<T>&& t)
{
  return std::move(t);
}

// from http://en.cppreference.com/w/cpp/algorithm/lower_bound
template<class ForwardIt, class T, class Compare=std::less<>>
ForwardIt binary_find(ForwardIt first, ForwardIt last, const T& value, Compare comp={})
{
  // Note: BOTH type T and the type after ForwardIt is dereferenced
  // must be implicitly convertible to BOTH Type1 and Type2, used in Compare.
  // This is stricter then lower_bound requirement (see above)

  first = std::lower_bound(first, last, value, comp);
  return first != last && (!comp(value, *first) ? first : last);
}

// for_each

template<typename Range, typename Func>
void for_each(const Range& range, Func func)
{
  std::for_each(std::begin(range), std::end(range), std::move(func));
}

template<typename Range, typename Func>
void modify_each(Range& range, Func&& func)
{
  std::for_each(std::begin(range), std::end(range), std::move(func));
}

// find_if

template<typename Range, typename Func>
auto find_if(Range& range, Func func)
{
  return std::find_if(std::begin(range), std::end(range), std::move(func));
}

// accumulate

template<typename Range, typename T>
auto accumulate(Range& range, T init)
{
  return std::accumulate(std::begin(range), std::end(range), init);
}

template<typename Range, typename T, typename Func>
auto accumulate(Range& range, T init, Func func)
{
  return std::accumulate(std::begin(range), std::end(range), init, std::move(func));
}

// lower_bound

template<typename Range, typename T>
auto lower_bound(Range& range, const T& value)
{
  return std::lower_bound(std::begin(range), std::end(range), value);
}

template<typename Range, typename T, typename Compare>
auto lower_bound(Range& range, const T& value, Compare cmp)
{
  return std::lower_bound(std::begin(range), std::end(range),
                          value, std::move(cmp));
}

// equal

template<typename Range1, typename Range2>
bool equal(const Range1& range1, const Range2& range2)
{
  return std::equal(std::begin(range1), std::end(range1), std::begin(range2), std::end(range2));
}

template<typename Range1, typename Range2, typename BinaryPredicate>
bool equal(const Range1& range1, const Range2& range2, BinaryPredicate p)
{
  return std::equal(std::begin(range1), std::end(range1), std::begin(range2), std::end(range2), std::move(p));
}

// max_element

template<typename Range>
auto max_element(Range& range)
{
  return std::max_element(std::begin(range), std::end(range));
}

template<typename Range, typename Compare>
auto max_element(Range& range, Compare cmp)
{
  return std::max_element(std::begin(range), std::end(range), std::move(cmp));
}

// max_element_by
template<typename Range, class KeyFunc>
auto max_element_by(Range& rng, KeyFunc&& key) -> decltype(std::begin(rng))
{
  auto first = std::begin(rng);
  auto last = std::end(rng);

  if (first == last)
    return last;

  auto largest = first;
  auto largest_value = key(*first);
  ++first;
  for (; first != last; ++first) {
    auto value = key(*first);
    if (largest_value > value) {
      largest = first;
      largest_value = value;
    }
  }
  return largest;
}


}  // namespace cpp

#endif /* INCLUDE_CPP_UTILS_ALGORITHM_CONTAINER_H_ */
