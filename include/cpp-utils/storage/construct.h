#ifndef CPP_CONSTRUCT_H
#define CPP_CONSTRUCT_H

#include <type_traits>
#include <memory>
#include <utility>
#include <iterator>
#include <new>

#include "../meta/require.h"

namespace cpp {

template<typename T, typename ...Args> inline
void construct(T* ptr, Args&&... args) {
  ::new(ptr) T(std::forward<Args>(args)...);
}

template<typename T, FUNC_REQUIRES(std::is_trivially_destructible<T>::value)> inline
void destruct(T*) { }

template<typename T, FUNC_REQUIRES(!std::is_trivially_destructible<T>::value)> inline
void destruct(T* ptr) {
  ptr->~T();
}

template<typename ForwardIterator, FUNC_REQUIRE(std::is_trivially_destructible<typename std::iterator_traits<ForwardIterator>::value_type>)> inline
void destruct(ForwardIterator, ForwardIterator) { }

template<typename ForwardIterator, FUNC_REQUIRE(!std::is_trivially_destructible<typename std::iterator_traits<ForwardIterator>::value_type>)>
void destruct(ForwardIterator first, ForwardIterator last) {
  for (; first != last; ++first) {
    destruct(std::addressof(*first));
  }
}

} // namespace cpp

#endif // CPP_CONSTRUCT_H
