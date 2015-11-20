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

#ifndef UTILS_FACTORY_H_
#define UTILS_FACTORY_H_

#include <type_traits>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/vector.hpp>
#include "core.h"

namespace cpp {

template<typename TypeList>
class Factory {
public:
  using Types = TypeList;

  template<typename CreateFunc, typename...Args>
  static typename CreateFunc::ResultType create(Args...args)
  {
    using namespace boost::mpl;

    typedef typename begin< Types >::type begin;
    typedef typename end< Types >::type   end;

    return search_result<begin, end, CreateFunc>::create(args...);
  }

private:
  template < typename Begin, typename End, typename F >
  struct search_result
  {
    template<typename...Args>
    static typename F::ResultType create(Args...args)
    {
      using namespace boost::mpl;

      auto result = F::template create< typename Begin::type >(args...);
      if (!result)
      {
        result = search_result< typename next< Begin >::type, End, F >::create(args...);
      }

      return result;
    }
  };

  template < typename End, typename F >
  struct search_result< End, End, F >
  {
    template<typename...Args>
    static typename F::ResultType create(Args...args)
    {
      return F::fail(args...);
    }
  };
};

} // namespace cpp

#endif /* UTILS_FACTORY_H_ */
