/// \file registry.h

#ifndef INCLUDE_CPP_UTILS_PATTERN_REGISTRY_H_
#define INCLUDE_CPP_UTILS_PATTERN_REGISTRY_H_

#include <memory>
#include <utility>
#include <string>

#include "../iterator_range.h"
#include "../make_unique.h"

namespace cpp {

template<typename T>
class simple_registry_entry
{
public:
  using factory = std::unique_ptr<T>(*)();

  explicit simple_registry_entry(
    const char* name, const char* description, const factory factory)
    : name_(name), description_(description), factory_(factory)
  { }

  template<typename V>
  static simple_registry_entry create(const char* name, const char* description)
  {
    return simple_registry_entry(name, description,
      []() -> std::unique_ptr<T> { return make_unique<V>(); });
  }

  std::unique_ptr<T> create() const { return factory_(); }

  const char* name() const { return name_; }
  const char* description() const { return description_; }

private:
  const char* name_;
  const char* description_;
  const factory factory_;
};

/// \brief compile time registry
///
/// \details inspired by \c llvm::Registry
template<typename T, typename Entry = simple_registry_entry<T>>
class registry
{
  class node;

public:
  using entry = Entry;

  registry();

  class iterator : public std::iterator<std::forward_iterator_tag, const entry>
  {
  public:
    explicit iterator(const node* n) : current_(n) {}

    bool operator==(const iterator& rhs) const { return current_ == rhs.current_; }
    bool operator!=(const iterator& rhs) const { return current_ != rhs.current_; }

    iterator& operator++()
    {
      current_ = current_->next_;
      return *this;
    }

    const entry& operator*() const { return current_->value_; }
    const entry* operator->() const { return &current_->value_; }

  private:
    const node* current_;
  };

  static iterator begin() { return iterator(head_); }
  static iterator end() { return iterator(nullptr); }

  static iterator_range<iterator> entries()
  {
    return make_range(begin(), end());
  }

  /// \brief add element to registry
  /// \tparam V type of registry element
  /// \param args arguments for registry entry
  template<typename V>
  class element
  {
  public:
    template<typename...Args>
    explicit element(Args&&...args)
      : node_(entry::template create<V>(std::forward<Args>(args)...))
    { }

  private:
    node node_;
  };

private:
  /// \brief internal list node
  class node
  {
  public:
    /// create new node in list
    template<typename...Args>
    node(Args&&...args)
      : next_(head_), value_(std::forward<Args>(args)...)
    {
      head_ = this;
    }

  private:
    /// pointer to next node in list
    const node* next_;

    /// value of list node
    const entry value_;

    friend class iterator;
  };

  /// pointer to first list node or \c nullptr if list is empty
  static node* head_;
};

template<typename T, typename U>
typename registry<T,U>::node* registry<T,U>::head_ = nullptr;

} // namespace cpp

#endif /* INCLUDE_CPP_UTILS_PATTERN_REGISTRY_H_ */
