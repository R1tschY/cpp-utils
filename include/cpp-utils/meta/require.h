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

#ifndef LIBS_CPP_UTILS_REQUIRE_H_
#define LIBS_CPP_UTILS_REQUIRE_H_

namespace cpp {

#define REQUIRE(...) typename std::enable_if<__VA_ARGS__::value>::type
#define REQUIRES(...) typename std::enable_if<__VA_ARGS__>::type

#define FUNC_REQUIRE(...) typename std::enable_if<__VA_ARGS__::value>::type* = nullptr
#define FUNC_REQUIRES(...) typename std::enable_if<__VA_ARGS__>::type* = nullptr

}  // namespace cpp

#endif /* LIBS_CPP_UTILS_REQUIRE_H_ */
