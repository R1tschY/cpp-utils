#include <boost/test/unit_test.hpp>
#include <cpp-utils/pattern/monointerface.h>
#include <cpp-utils/resourcehandler.h>

namespace {

class I {
public: 
	I() { }
	virtual ~I() { }
	
	virtual int test() = 0;
};

class A : public I {
public:
	int test() override {
		return 42;
	}
};

}


using HANDLE = void*;
HANDLE CreateHandle() { return reinterpret_cast<HANDLE>(-1); }
void DestroyHandle(HANDLE) { }

using Handle = cpp::resource_handler<HANDLE, struct HandleTag>;
namespace cpp {
template<> void Handle::cleanup() noexcept {
	if (resource_)
	  DestroyHandle(resource_);
}
}

BOOST_AUTO_TEST_SUITE(Pattern_Tests)

BOOST_AUTO_TEST_CASE(MonoInterface_All) {
	using MonoI = cpp::mono_interface<I>;
	
	MonoI mono(std::unique_ptr<I>(new A()));
  BOOST_CHECK_EQUAL(42, mono->test());
  BOOST_CHECK_EQUAL(42, (*mono).test());
  BOOST_CHECK_EQUAL(42, (&mono)->test());
  
  MonoI mono2;
  BOOST_CHECK_EQUAL(42, mono->test());
  
  BOOST_CHECK_EQUAL(42, MonoI::get().test());
  BOOST_CHECK_EQUAL(42, MonoI::instance().test());
  BOOST_CHECK_EQUAL(42, MonoI::pointer()->test());
}

BOOST_AUTO_TEST_CASE(ResourceHandler_All) {
	Handle h(CreateHandle());
}

BOOST_AUTO_TEST_SUITE_END()

