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

#include <memory>
#include <cassert>

namespace cpp {

/// Idea from http://accu.org/index.php/journals/2085
template<typename AbstractClass, class Tag = void>
class mono_interface final
{
public:
  explicit mono_interface(std::unique_ptr<AbstractClass> new_instance) 
  {
    set(std::move(new_instance));
  }
  
  mono_interface() 
  {
    assert(instance_ != nullptr);
  }
  
  AbstractClass* operator->() {
  	return pointer();
  }
  
  const AbstractClass* operator->() const {
  	return pointer();
  }
  
  AbstractClass& operator*() {
  	return *instance_;
  }
  
  const AbstractClass& operator*() const {
  	return *instance_;
  }
  
  AbstractClass* operator&() {
  	return pointer();
  }
  
  const AbstractClass* operator&() const {
  	return pointer();
  }
  
  static AbstractClass& instance() {
  	return *instance_;
  }
  
  static AbstractClass& get() {
  	return *instance_;
  }
  
  static AbstractClass* pointer() {
  	return instance_.get();
  }
  
  static void set(std::unique_ptr<AbstractClass> new_instance) {
    assert(new_instance != nullptr);
    assert(instance_ == nullptr);
      
    instance_ = std::move(new_instance);
  }

private:
  static std::unique_ptr<AbstractClass> instance_; // TODO: make atomic
};

template<typename AbstractClass, typename Tag>
std::unique_ptr<AbstractClass> mono_interface<AbstractClass, Tag>::instance_;

}
