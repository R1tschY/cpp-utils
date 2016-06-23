#include <boost/test/unit_test.hpp>

#include <cpp-utils/pattern/registry.h>
#include <cpp-utils/algorithm/container.h>

using namespace cpp;

namespace {

class Module
{
public:
  virtual ~Module() = default;

  virtual void init() = 0;

  int init_called = 0;
};

class MyModule1 : public Module
{
  void init() override { init_called++; }
};
class MyModule2 : public Module
{
  void init() override { init_called++; }
};

registry<Module>::element<MyModule1> MyModuleNode1("module1", "description1");
registry<Module>::element<MyModule2> MyModuleNode2("module2", "description1");

}  // namespace

BOOST_AUTO_TEST_SUITE(Registry_Tests)

BOOST_AUTO_TEST_CASE(default_use_case)
{
  auto entries = registry<Module>::entries();
  BOOST_CHECK_EQUAL(2, std::distance(entries.begin(), entries.end()));

  std::vector<std::string> names;
  cpp::transform(entries, names, [](auto& entry) { return entry.name(); });
  cpp::sort(names);
  BOOST_CHECK(
    cpp::equal(names, make_list({"module1", "module2"}))
  );

  std::vector<std::unique_ptr<Module>> modules;
  cpp::transform(entries, modules, [](auto& entry) { return entry.create(); });
  cpp::for_each(modules, [](auto& module){ module->init(); });
  BOOST_CHECK(
    cpp::all_of(modules, [](auto& module){ return module->init_called == 1; })
  );
}

BOOST_AUTO_TEST_SUITE_END()
