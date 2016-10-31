#pragma once

#include <cpp-utils/pattern/embedded_pimple.h>

namespace cpp {

/// \brief
class embedded_pimple_test
{
public:
    embedded_pimple_test();
    ~embedded_pimple_test();

    int getA() const;
    int getB() const;

private:
    struct Private;
    cpp::embedded_pimple<Private, 64> d_;
};

} // namespace cpp
