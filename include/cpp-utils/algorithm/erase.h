#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <memory>
#include <algorithm>

namespace cpp {

template<typename Container, typename T>
Container& erase(Container& container, const T& val) {
  auto old_end = std::end(container);
  auto new_end = std::remove(std::begin(container), old_end, val);
  container.erase(new_end, old_end);
  return container;
}

template<typename Container, typename Predicate>
Container& erase_if(Container& container, Predicate pred) {
  auto old_end = std::end(container);
  auto new_end = std::remove_if(std::begin(container), old_end, pred);
  container.erase(new_end, old_end);
  return container;
}

} // namespace extra

#endif // ALGORITHM_H
