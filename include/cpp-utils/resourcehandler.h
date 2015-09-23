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
 
#include <cassert>
#include <memory>

namespace cpp {

/// Idea from http://accu.org/index.php/journals/2086
template<typename T, typename Tag = void>
class resource_handler final
{
public:
  resource_handler() noexcept = default;
  
  explicit resource_handler(T resource) noexcept :
    resource_{resource}
  { }
    
  resource_handler(const resource_handler&) = delete;  
  resource_handler& operator=(const resource_handler&) = delete;
  
  resource_handler(resource_handler&& other) noexcept : 
  	resource_{other.resource_} 
  {
  	other.resource_ = {};
  }

  resource_handler& operator=(resource_handler&& other) noexcept 
  {
    assert(this != std::addressof(other));
    
    cleanup();
    resource_ = other.resource_;
    other.resource_ = {};
    return *this;
  }

  ~resource_handler() 
  {
  	cleanup();
  }
  
  operator const T&() const noexcept 
  {
    return resource_;
  }

  T* operator&() noexcept 
  {
    cleanup();
    return &resource_;
  }
  
private:
  T resource_{};
  
  void cleanup() noexcept;
  
  static constexpr bool return_false() noexcept { return false; }
};

template<typename T, typename Tag>
void resource_handler<T, Tag>::cleanup() noexcept {
  static_assert(return_false(), "This function must be explicitly specialized.");
}

}
