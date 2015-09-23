/*
 *      Copyright 2015 R1tschY <r1tschy@yahoo.de>
 *      
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef UTILS_META_STATICFOREACH_H_
#define UTILS_META_STATICFOREACH_H_

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/vector.hpp>

namespace detail {

template < typename Begin, typename End, typename F >
struct static_for_each
{
  static void apply( )
  {
    using namespace boost::mpl;
    typedef typename Begin::type currentType;

    F::template apply< currentType >();
    static_for_each< typename next< Begin >::type, End, F >::apply();
  }
};


template < typename End, typename F >
struct static_for_each< End, End, F >
{
  static void apply( )
  {
  }
};

} // namespace detail


template < typename Sequence, typename F >
void static_for_each( )
{
  using namespace boost::mpl;

  typedef typename begin< Sequence >::type begin;
  typedef typename end< Sequence >::type   end;

  detail::static_for_each< begin, end, F >::apply();
}

#endif /* UTILS_META_STATICFOREACH_H_ */
