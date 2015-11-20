#include "google/gtest/gtest.h"

#include <cpp-utils/preprocessor.h>

// CPP_NARG

TEST(Preprocessor_NARGS, Simple)
{
  EXPECT_EQ(0, CPP_NARGS());
  EXPECT_EQ(1, CPP_NARGS(a));
  EXPECT_EQ(2, CPP_NARGS(a, b));
  EXPECT_EQ(12, CPP_NARGS(a, b, c, d, e, f, g, h, i, j, k, l));
}

TEST(Preprocessor_NARGS, Composed)
{
  EXPECT_EQ(2, CPP_NARGS(a, (b)));
  EXPECT_EQ(2, CPP_NARGS(a, (b, c)));
  EXPECT_EQ(1, CPP_NARGS((b, c)));
}

TEST(Preprocessor_NARGS, StringConstant)
{
  EXPECT_EQ("0", CPP_STRINGIFY(CPP_NARGS()));
  EXPECT_EQ("1", CPP_STRINGIFY(CPP_NARGS(a)));
  EXPECT_EQ("2", CPP_STRINGIFY(CPP_NARGS(a, b)));
  EXPECT_EQ("12", CPP_STRINGIFY(CPP_NARGS(a, b, c, d, e, f, g, h, i, j, k, l)));
}

TEST(Preprocessor_NARGS, Concat)
{
  EXPECT_EQ("x0x", CPP_STRINGIFY(CPP_CONCAT(x,CPP_NARGS(),x)));
  EXPECT_EQ("X1XX", CPP_STRINGIFY(CPP_CONCAT(X,CPP_NARGS(a),XX)));
  EXPECT_EQ("2AA", CPP_STRINGIFY(CPP_CONCAT(CPP_NARGS(a, b),AA)));
}

// CPP_VFUNC

#define SUM0() (0)
#define SUM1(x) (x)
#define SUM2(x,y) ((x) + (y))
#define SUM3(x,y,z) ((x) + (y) + (z))

static int sum0() { return 0; }
static int sum1(int x) { return x; }
static int sum2(int x, int y) { return x + y; }
static int sum3(int x, int y, int z) { return x + y + z; }

TEST(Preprocessor_VFUNC, MacroFunction)
{
#define SUM(...) CPP_VFUNC(SUM, __VA_ARGS__)
  EXPECT_EQ(6, SUM(1,2,3));

  int x = 3;
  EXPECT_EQ(6, SUM(1,2,x));
  EXPECT_EQ(6, SUM(x,2,1));

  //EXPECT_EQ(SUM(), 0);
#undef SUM
}

TEST(Preprocessor_VFUNC, CFunction)
{
#define SUM(...) CPP_VFUNC(sum, __VA_ARGS__)
  EXPECT_EQ(6, SUM(1,2,3));

  int x = 3;
  EXPECT_EQ(6, SUM(1,2,x));
  EXPECT_EQ(6, SUM(x,2,1));

  EXPECT_EQ(1, SUM(1));
  //EXPECT_EQ(SUM(), 0);
#undef SUM
}

// CPP_CONCAT

TEST(Preprocessor_CONCAT, Concat)
{
#define TEST_MACRO 42
  int xXx = 42;

  EXPECT_EQ(42, CPP_CONCAT(x,X,x));
  EXPECT_EQ(42, CPP_CONCAT(CPP_CONCAT(TEST,_),MACRO));
  EXPECT_EQ("xXx", CPP_STRINGIFY(CPP_CONCAT(CPP_CONCAT(x,X),x)));
  EXPECT_EQ("xXx", CPP_STRINGIFY(CPP_CONCAT(x,X,x)));

#undef TEST_MACRO
}

// CPP_STRINGIFY

TEST(Preprocessor_STRINGIFY, Concat)
{
  EXPECT_EQ("xXx", CPP_STRINGIFY(xXx));
  EXPECT_EQ("1+1", CPP_STRINGIFY(1+1));
  EXPECT_EQ("&1+1~~", CPP_STRINGIFY(&1+1~~));
  EXPECT_EQ("(1,1)", CPP_STRINGIFY((1,1)));
  EXPECT_EQ("(std::map<int,int>)", CPP_STRINGIFY((std::map<int,int>)));
}

// CPP_MACRO_BEGIN/END

TEST(Preprocessor_MACRO_BEGIN_END, SetVariable)
{
#define TEST_MACRO(x) CPP_MACRO_BEGIN int i = 42; x = i; CPP_MACRO_END

  int x;
  TEST_MACRO(x);
  EXPECT_EQ(42, x);

#undef TEST_MACRO
}
