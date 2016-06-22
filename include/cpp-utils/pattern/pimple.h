#ifndef LIBS_CPP_UTILS_PIMPLE_H_
#define LIBS_CPP_UTILS_PIMPLE_H_

#include <memory>
#include <utility>
#include <type_traits>

namespace cpp {

template<typename Private>
class pimple : private std::unique_ptr<Private>
{
  using base = std::unique_ptr<Private>;

public:
  template<typename...Args>
  pimple(Args...args)
  : base(new Private(std::forward<Args>(args)...))
  { }

  pimple(std::unique_ptr<Private> d)
  : base(std::move(d))
  { }

  const Private& operator*() const { return *get(); }
  Private& operator*() { return *get(); }

  const Private* operator->() const { return get(); }
  Private* operator->() { return get(); }

  const Private* get() const { return base::get(); }
  Private* get() { return base::get(); }
};
/*
template<typename Class>
class class_private_base
{
public:
  class_private_base() : q_(nullptr) { } // q_ is set by class_pimple

  const Class* getClass() const { assert(q_ != nullptr); return q_; }
  Class* getClass() { assert(q_ != nullptr); return q_; }

private:
  Class*const q_;

  void set(Class* q) { assert(q_ == nullptr && q != nullptr); q_ = q; }

  template<typename Class, typename Private = Class::Private>
  friend class class_pimple;
};

template<typename Class, typename Private = Class::Private>
class class_pimple : private std::unique_ptr<Private>
{
  static_assert(std::is_base_of<pimple_base<Class>, Private>::value, "");
  using base = std::unique_ptr<Private>;

public:
  template<typename...Args>
  class_pimple(Class* c, Args...args)
  : base(new Private(std::forward<Args>(args)...))
  {
    static_cast<pimple_base<Class>*>(get())->set(c);
  }

  const Private& operator*() const { return *get(); }
  Private& operator*() { return *get(); }

  const Private* operator->() const { return get(); }
  Private* operator->() { return get(); }

  const Private* get() const { return base::get(); }
  Private* get() { return base::get(); }
};*/

}  // namespace cpp

#endif /* LIBS_CPP_UTILS_PIMPLE_H_ */
