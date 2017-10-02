#ifndef INCLUDE_CPP_UTILS_TO_H_
#define INCLUDE_CPP_UTILS_TO_H_

#include <type_traits>

namespace cpp {

// down_cast

template<typename Src, typename BasePtr>
typename std::enable_if<
  std::is_base_of<std::remove_pointer_t<BasePtr>, Src>::value && std::is_pointer<BasePtr>::value,
  std::remove_pointer_t<BasePtr>
>::type
to(Src* src)
{
  return src ? static_cast<BasePtr>(src) : nullptr;
}

template<typename Src, typename BaseRef>
typename std::enable_if<
  std::is_base_of<std::remove_reference_t<BaseRef>, Src>::value && std::is_reference<BaseRef>::value,
  std::remove_reference_t<BaseRef>>::type
to(Src& src)
{
  return static_cast<BaseRef>(src);
}

// upcast

template<typename Base, typename DerivedPtr>
typename std::enable_if<
  std::is_base_of<Base, std::remove_pointer_t<DerivedPtr>>::value && std::is_pointer<DerivedPtr>::value,
  std::remove_pointer_t<DerivedPtr>>::type
to(Base* base)
{
  // use references for std::bad_cast
  return base ? &dynamic_cast<DerivedPtr>(*base) : nullptr;
}

template<typename Base, typename DerivedPtr>
typename std::enable_if<
  std::is_base_of<Base, std::remove_reference_t<DerivedPtr>>::value && std::is_reference<DerivedPtr>::value,
  std::remove_reference_t<DerivedPtr>>::type
to(Base& base)
{
  return dynamic_cast<DerivedPtr>(base);
}

}  // namespace cpp

#endif // INCLUDE_CPP_UTILS_TO_H_
