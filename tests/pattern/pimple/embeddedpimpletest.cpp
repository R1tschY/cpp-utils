#include "embeddedpimpletest.h"

namespace cpp {

struct embedded_pimple_test::Private
{
    Private(int a, int b)
    : a_(a), b_(b)
    { }

    int a_;
    int b_;
};

embedded_pimple_test::embedded_pimple_test()
: d_(42, 67)
{ }

embedded_pimple_test::~embedded_pimple_test() { }

int embedded_pimple_test::getA() const { return d_->a_; }
int embedded_pimple_test::getB() const { return d_->b_; }

} // namespace cpp
