#include <gtest/gtest.h>
#include "../src/SapidFunctionCallList.h"

extern SEXP spdFunctionCallList();

TEST(SapidFunctionCallList, DeclCallList)
{
  printf("1\n");
  SEXP list = spdFunctionCallList();
  printf("2\n");
}
