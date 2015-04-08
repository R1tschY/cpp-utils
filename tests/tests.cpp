#include "google/gtest/gtest.h"
#include "../monointerface.h"
#include "../resourcehandler.h"

namespace {

class I {
public: 
	I() { }
	virtual ~I() { }
	
	int test() = 0;
}

class A {
public:
	int test() override {
		return 42;
	}
};

}

TEST(MonoInterface, All) {
	using MonoI = cpp::mono_interface<I>;
	
	MonoI mono(new A());
  EXPECT_EQ(42, mono->test());
  EXPECT_EQ(42, (*mono).test());
  EXPECT_EQ(42, (&mono)->test());
  
  MonoI mono2();
  EXPECT_EQ(42, mono->test());
  
  EXPECT_EQ(42, MonoI::get().test());
  EXPECT_EQ(42, MonoI::instance().test());
  EXPECT_EQ(42, MonoI::pointer()->test());
}

using HANDLE = void*;
HANDLE CreateHandle() { return reinterpret_cast<HANDLE>(-1); }
void DestroyHandle(HANDLE) { }

TEST(ResourceHandler, All) {
	using Handle = cpp::resource_handler<HANDLE, struct HandleTag>;
	template<> void Handle::Cleanup() noexcept {
		if (resource_)
		  DestroyHandle(resource_);
	}
	
	Handle h(CreateHandle());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
