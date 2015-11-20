#ifndef LIBS_CPP_UTILS_ARRAY_VIEW_H_
#define LIBS_CPP_UTILS_ARRAY_VIEW_H_

#include "../../3th-party/gsl/include/span.h"

namespace cpp {

template<typename Args...>
using array_view = gsl::span<Args...>;

} // namespace cpp

#endif /* LIBS_CPP_UTILS_ARRAY_VIEW_H_ */
