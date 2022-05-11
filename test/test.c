#include "libgeometry/geometry.h"
#include "libgeometry/function.h"
#include "libgeometry/figur_checking.c"
#include "ctest.h"

CTEST(figur_checking, name_1)
{
    char input[25] = "circle(1, 2, 3)\0";
    const int expected = 1;
    const int result = figur_checking(input);
    ASSERT_EQUAL(expected, result);
}

CTEST(figur_checking, name_2)
{
    char input[25] = "circl(1, 2, 3)\0";
    const int expected = 0;
    const int result = figur_checking(input);
    ASSERT_EQUAL(expected, result);
}

CTEST(figur_checking, name_3)
{
    char input[25] = "circli(1, 2, 3)\0";
    const int expected = 0;
    const int result = figur_checking(input);
    ASSERT_EQUAL(expected, result);
}

CTEST(figur_checking, name_4)
{
    char input[25] = "cir cle(1, 2, 3)\0";
    const int expected = 0;
    const int result = figur_checking(input);
    ASSERT_EQUAL(expected, result);
}