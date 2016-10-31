#ifndef LIBS_CPP_UTILS_PIMPLE_H_
#define LIBS_CPP_UTILS_PIMPLE_H_

#include <memory>
#include <utility>
#include <type_traits>
#include <cstddef>
#include "../storage/storage.h"
#include "../storage/construct.h"
#include "../copy_policy.h"

namespace cpp {

template<typename Private, size_t N, size_t Alignment=alignof(size_t)>
class embedded_pimple : private cpp::noncopyable
{
    static_assert(N > 0, "");
    static_assert(Alignment > 0, "");
public:
  template<typename...Args>
  embedded_pimple(Args...args)
  {
      static_assert(sizeof(Private) <= N, "");
      static_assert(Alignment % alignof(Private) == 0, "");

      cpp::construct(get(), std::forward<Args>(args)...);
  }

  ~embedded_pimple()
  {
      cpp::destruct(get());
  }

  const Private& operator*() const { return *get(); }
  Private& operator*() { return *get(); }

  const Private* operator->() const { return get(); }
  Private* operator->() { return get(); }

  const Private* get() const { return reinterpret_cast<const Private*>(&data_); }
  Private* get() { return reinterpret_cast<Private*>(&data_); }

private:
  typename std::aligned_storage<N, Alignment>::type data_;
};

}  // namespace cpp

#endif /* LIBS_CPP_UTILS_PIMPLE_H_ */
