#include <boost/test/unit_test.hpp>

#include <cpp-utils/preprocessor.h>

BOOST_AUTO_TEST_SUITE(Preprocessor_Tests)

// CPP_NARG

BOOST_AUTO_TEST_CASE(Preprocessor_NARGS_Simple)
{
  BOOST_CHECK_EQUAL(0, CPP_NARGS());
  BOOST_CHECK_EQUAL(1, CPP_NARGS(a));
  BOOST_CHECK_EQUAL(2, CPP_NARGS(a, b));
  BOOST_CHECK_EQUAL(12, CPP_NARGS(a, b, c, d, e, f, g, h, i, j, k, l));
}

BOOST_AUTO_TEST_CASE(Preprocessor_NARGS_Composed)
{
  BOOST_CHECK_EQUAL(2, CPP_NARGS(a, (b)));
  BOOST_CHECK_EQUAL(2, CPP_NARGS(a, (b, c)));
  BOOST_CHECK_EQUAL(1, CPP_NARGS((b, c)));
}

BOOST_AUTO_TEST_CASE(Preprocessor_NARGS_StringConstant)
{
  BOOST_CHECK_EQUAL("0", CPP_STRINGIFY(CPP_NARGS()));
  BOOST_CHECK_EQUAL("1", CPP_STRINGIFY(CPP_NARGS(a)));
  BOOST_CHECK_EQUAL("2", CPP_STRINGIFY(CPP_NARGS(a, b)));
  BOOST_CHECK_EQUAL("12", CPP_STRINGIFY(CPP_NARGS(a, b, c, d, e, f, g, h, i, j, k, l)));
}

BOOST_AUTO_TEST_CASE(Preprocessor_NARGS_Concat)
{
  BOOST_CHECK_EQUAL("x0x", CPP_STRINGIFY(CPP_CONCAT(x,CPP_NARGS(),x)));
  BOOST_CHECK_EQUAL("X1XX", CPP_STRINGIFY(CPP_CONCAT(X,CPP_NARGS(a),XX)));
  BOOST_CHECK_EQUAL("2AA", CPP_STRINGIFY(CPP_CONCAT(CPP_NARGS(a, b),AA)));
}

// CPP_VFUNC

#define SUM0() (0)
#define SUM1(x) (x)
#define SUM2(x,y) ((x) + (y))
#define SUM3(x,y,z) ((x) + (y) + (z))

int sum0() { return 0; }
int sum1(int x) { return x; }
int sum2(int x, int y) { return x + y; }
int sum3(int x, int y, int z) { return x + y + z; }

BOOST_AUTO_TEST_CASE(Preprocessor_VFUNC_MacroFunction)
{
#define SUM(...) CPP_VFUNC(SUM, __VA_ARGS__)
  BOOST_CHECK_EQUAL(6, SUM(1,2,3));

  int x = 3;
  BOOST_CHECK_EQUAL(6, SUM(1,2,x));
  BOOST_CHECK_EQUAL(6, SUM(x,2,1));

  //BOOST_CHECK_EQUAL(SUM(), 0);
#undef SUM
}

BOOST_AUTO_TEST_CASE(Preprocessor_VFUNC_CFunction)
{
#define SUM(...) CPP_VFUNC(sum, __VA_ARGS__)
  BOOST_CHECK_EQUAL(6, SUM(1,2,3));

  int x = 3;
  BOOST_CHECK_EQUAL(6, SUM(1,2,x));
  BOOST_CHECK_EQUAL(6, SUM(x,2,1));

  BOOST_CHECK_EQUAL(1, SUM(1));
  //BOOST_CHECK_EQUAL(SUM(), 0);
#undef SUM
}

// CPP_CONCAT

BOOST_AUTO_TEST_CASE(Preprocessor_CONCAT_Concat)
{
#define TEST_MACRO 42
  int xXx = 42;

  BOOST_CHECK_EQUAL(42, CPP_CONCAT(x,X,x));
  BOOST_CHECK_EQUAL(42, CPP_CONCAT(CPP_CONCAT(TEST,_),MACRO));
  BOOST_CHECK_EQUAL("xXx", CPP_STRINGIFY(CPP_CONCAT(CPP_CONCAT(x,X),x)));
  BOOST_CHECK_EQUAL("xXx", CPP_STRINGIFY(CPP_CONCAT(x,X,x)));

#undef TEST_MACRO
}

// CPP_STRINGIFY

BOOST_AUTO_TEST_CASE(Preprocessor_STRINGIFY_Concat)
{
  BOOST_CHECK_EQUAL("xXx", CPP_STRINGIFY(xXx));
  BOOST_CHECK_EQUAL("1+1", CPP_STRINGIFY(1+1));
  BOOST_CHECK_EQUAL("&1+1~~", CPP_STRINGIFY(&1+1~~));
  BOOST_CHECK_EQUAL("(1,1)", CPP_STRINGIFY((1,1)));
  BOOST_CHECK_EQUAL("(std::map<int,int>)", CPP_STRINGIFY((std::map<int,int>)));
}

// CPP_MACRO_BEGIN/END

BOOST_AUTO_TEST_CASE(Preprocessor_MACRO_BEGIN_END_SetVariable)
{
#define TEST_MACRO(x) CPP_MACRO_BEGIN int i = 42; x = i; CPP_MACRO_END

  int x;
  if (1)
	  TEST_MACRO(x);
  BOOST_CHECK_EQUAL(42, x);

#undef TEST_MACRO
}

BOOST_AUTO_TEST_SUITE_END()
