#ifndef UNINITIZED_H
#define UNINITIZED_H

#include <utility>

#include "../copy_policy.h"
#include "construct.h"
#include "storage.h"

namespace cpp {

/// \todo cpp::use_copy_policy_of needed?
template<typename T>
class uninitialized : private cpp::use_copy_policy_of<T>
{
public:
  constexpr uninitialized() { }

  explicit uninitialized(const uninitialized& other) { construct(other); }
  explicit uninitialized(uninitialized&& other) { construct(std::move(other)); }

  template<class... Args>
  void construct(Args&&... args) {
    cpp::construct(getPointer(), std::forward<Args>(args)...);
  }

  void destruct() {
    cpp::destruct(getPointer());
  }

  uninitialized& operator=(const uninitialized& t) {
    get() = t.get();
    return *this;
  }
  uninitialized& operator=(uninitialized&& t) {
    get() = std::move(t.get());
    return *this;
  }

  T* operator -> () { return getPointer(); }    
  T& operator * () { return get(); }    
  T* getPointer() { return reinterpret_cast<T*>(&data); }    
  T& get() { return *reinterpret_cast<T*>(&data); }
  
  const T* operator -> () const { return getPointer(); }    
  const T& operator * () const { return get(); }    
  const T* getPointer() const { return reinterpret_cast<const T*>(&data); }    
  const T& get() const { return *reinterpret_cast<const T*>(&data); }

private:
  storage<T> data;
};

} // namespace cpp

#endif // UNINITIZED_H
