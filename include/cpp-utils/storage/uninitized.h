#ifndef UNINITIZED_H
#define UNINITIZED_H

#include <utility>

#include "../copy_policy.h"
#include "construct.h"
#include "storage.h"

namespace cpp {

/// \brief define lifetime of \p T by runtime
/// \warning use with caution: first construct than use than destruct. No information
/// is stored whether \p T is constructed.
/// Use std::optional, std::experimental::optional or boost::optional if you want this information.
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
  T* getPointer() { return reinterpret_cast<T*>(&data_); }    
  T& get() { return *reinterpret_cast<T*>(&data_); }
  
  const T* operator -> () const { return getPointer(); }    
  const T& operator * () const { return get(); }    
  const T* getPointer() const { return reinterpret_cast<const T*>(&data_); }    
  const T& get() const { return *reinterpret_cast<const T*>(&data_); }

private:
  storage<T> data_;
};

template<typename T>
class scoped_lifetime
{
public:
  template<class... Args>
  scoped_lifetime(uninitialized<T>& value, Args&&... args)
  : value_(value)
  {
    value_.construct(std::forward<Args>(args)...);
  }

  ~scoped_lifetime()
  {
    value_.destruct();
  }

  // TODO: copy/move

  T* operator -> () { return value_.getPointer(); }
  T& operator * () { return value_.get(); }
  T* getPointer() { return value_.getPointer(); }
  T& get() { return value_.get(); }

  const T* operator -> () const { return getPointer(); }
  const T& operator * () const { return get(); }
  const T* getPointer() const { return value_.getPointer(); }
  const T& get() const { return value_.get(); }

private:
  uninitialized<T>& value_;
};

} // namespace cpp

#endif // UNINITIZED_H
