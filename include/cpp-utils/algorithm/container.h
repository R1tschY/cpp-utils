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

/// \brief std::equal for ranges
template<typename Range1, typename Range2>
bool equal(const Range1& r1, const Range2& r2)
{
  return std::equal(std::begin(r1), std::end(r1), std::begin(r2), std::end(r2));
}

/// \brief std::for_each for ranges
template<typename Range1, typename Func>
void for_each(const Range1& r1, Func&& func)
{
  std::for_each(std::begin(r1), std::end(r1), std::move(func));
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

}  // namespace cpp

#endif /* INCLUDE_CPP_UTILS_ALGORITHM_CONTAINER_H_ */
