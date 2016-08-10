///
/// Copyright (c) 2016 R1tschY
/// 
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to 
/// deal in the Software without restriction, including without limitation the 
/// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
/// sell copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
/// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
/// IN THE SOFTWARE.
///

#ifndef CPP_UTILS_IOSTREAMS_SMALLSTRINGSTREAM_H_
#define CPP_UTILS_IOSTREAMS_SMALLSTRINGSTREAM_H_

#include <sstream>

namespace cpp {

template<typename CharT, std::size_t N, typename Traits = std::char_traits<CharT>, typename Alloc = std::allocator<CharT>>
class basic_small_ostringstream : public std::basic_ostringstream<CharT, Traits, Alloc>
{
  using base = std::basic_ostringstream<CharT, Traits, Alloc>;
public:
  explicit
  basic_small_ostringstream(std::ios_base::openmode mode = std::ios_base::out)
  : base(mode)
  {
    base::rdbuf()->pubsetbuf(buffer_, cpp::length(buffer_));
  }

private:
  CharT buffer_[N];
};

template<std::size_t N>
using small_ostringstream = basic_small_ostringstream<char, N>;

template<std::size_t N>
using small_owstringstream = basic_small_ostringstream<wchar_t, N>;

} // namespace cpp

#endif /* CPP_UTILS_IOSTREAMS_SMALLSTRINGSTREAM_H_ */
