#include "libgeometry/geometry.h"
#include "libgeometry/function.h"
#include "libgeometry/figur_checking.c"
#include "libgeometry/input_arg.c"
#include "libgeometry/fun_area_perimetr.c"
#include "libgeometry/fun_check_intersection.c"

#include "../thirdparty/ctest.h"

CTEST(figur_checking, name_1)
{
    char input[25] = "circle(1, 2, 3)\n";
    const int expected = 1;
    const int result = figur_checking(input);
    ASSERT_EQUAL(expected, result);
}

CTEST(figur_checking, name_2)
{
    char input[25] = "circl(1, 2, 3)\n";
    const int expected = 0;
    const int result = figur_checking(input);
    ASSERT_EQUAL(expected, result);
}

CTEST(figur_checking, name_3)
{
    char input[25] = "circli(1, 2, 3)\n";
    const int expected = 0;
    const int result = figur_checking(input);
    ASSERT_EQUAL(expected, result);
}

CTEST(figur_checking, name_4)
{
    char input[25] = "cir cle(1, 2, 3)\n";
    const int expected = 0;
    const int result = figur_checking(input);
    ASSERT_EQUAL(expected, result);
}


CTEST(input_arg, figur_1)
{
    int result = 0;
    char input[25] = "circle(1, 2, 3)\n";
    StructCircle circle_test;
    StructCircle expected = {{1, 2}, 3};
    
    circle_test = input_arg(input);
    if (circle_test.point[0] == expected.point[0] && circle_test.point[1] == expected.point[1] && circle_test.radius == expected.radius) 
        result = 1;
    else
        result = 0;

    ASSERT_EQUAL(1, result);
}

CTEST(input_arg, figur_2)
{
    int result = 0;
    char input[25] = "circle(1 2, 3)\n";
    StructCircle circle_test;
    StructCircle expected = {{1, 2}, 3};
    
    circle_test = input_arg(input);
    if (circle_test.point[0] == expected.point[0] && circle_test.point[1] == expected.point[1] && circle_test.radius == expected.radius) 
        result = 1;
    else
        result = 0;

    ASSERT_EQUAL(0, result);
}

CTEST(input_arg, figur_3)
{
    int result = 0;
    char input[25] = "circle(1..0, 2, 3)\n";
    StructCircle circle_test;
    StructCircle expected = {{1, 2}, 3};
    
    circle_test = input_arg(input);
    if (circle_test.point[0] == expected.point[0] && circle_test.point[1] == expected.point[1] && circle_test.radius == expected.radius) 
        result = 1;
    else
        result = 0;

    ASSERT_EQUAL(0, result);
}

CTEST(input_arg, figur_4)
{
    int result = 0;
    char input[25] = "circle(1, 2, -3)\n";
    StructCircle circle_test;
    StructCircle expected = {{1, 2}, 3};
    
    circle_test = input_arg(input);
    if (circle_test.point[0] == expected.point[0] && circle_test.point[1] == expected.point[1] && circle_test.radius == expected.radius) 
        result = 1;
    else
        result = 0;

    ASSERT_EQUAL(0, result);
}

CTEST(input_arg, figur_5)
{
    int result = 0;
    char input[25] = "circle(1, 2, 3, 4)\n";
    StructCircle circle_test;
    StructCircle expected = {{1, 2}, 3};
    
    circle_test = input_arg(input);
    if (circle_test.point[0] == expected.point[0] && circle_test.point[1] == expected.point[1] && circle_test.radius == expected.radius) 
        result = 1;
    else
        result = 0;

    ASSERT_EQUAL(0, result);
}

CTEST(input_arg, figur_6)
{
    int result = 0;
    char input[25] = "circle(1, , 3)\n";
    StructCircle circle_test;
    StructCircle expected = {{1, 2}, 3};
    
    circle_test = input_arg(input);
    if (circle_test.point[0] == expected.point[0] && circle_test.point[1] == expected.point[1] && circle_test.radius == expected.radius) 
        result = 1;
    else
        result = 0;

    ASSERT_EQUAL(0, result);
}

CTEST(input_arg, figur_7) // !
{
    int result = 0;
    char input[25] = "circle(1, 2 3 , 3)\n";
    StructCircle circle_test;
    StructCircle expected = {{1, 2}, 3};
    
    circle_test = input_arg(input);
    if (circle_test.point[0] == expected.point[0] && circle_test.point[1] == expected.point[1] && circle_test.radius == expected.radius) 
        result = 1;
    else
        result = 0;

    ASSERT_EQUAL(0, result);
}

CTEST(input_arg, figur_8)
{
    int result = 0;
    char input[25] = "circle(1, --2, 3)\n";
    StructCircle circle_test;
    StructCircle expected = {{1, 2}, 3};
    
    circle_test = input_arg(input);
    if (circle_test.point[0] == expected.point[0] && circle_test.point[1] == expected.point[1] && circle_test.radius == expected.radius) 
        result = 1;
    else
        result = 0;

    ASSERT_EQUAL(0, result);
}

CTEST(input_arg, figur_9)
{
    int result = 0;
    char input[L_MAX] = "circle(1                 ,                     2               ,         3)\n";
    StructCircle circle_test;
    StructCircle expected = {{1, 2}, 3};
    
    circle_test = input_arg(input);
    if (circle_test.point[0] == expected.point[0] && circle_test.point[1] == expected.point[1] && circle_test.radius == expected.radius) 
        result = 1;
    else
        result = 0;

    ASSERT_EQUAL(1, result);
}


CTEST(fun_area_perimetr, geometry_1)
{
    int result = 0;
    float r = 3;
    StructCircle circle_test = {{1, 2}, 3};
    
    struct info info_test = fun_area_perimetr(circle_test);
    const struct info expected = {2 * M_PI * r, M_PI * r * r};
    if (info_test.perimeter == expected.perimeter && info_test.area == expected.area) 
        result = 1;
    else
        result = 0;

    ASSERT_EQUAL(1, result);
}

CTEST(fun_area_perimetr, geometry_2)
{
    int result = 0;
    float r = 5;
    StructCircle circle_test = {{1, 2}, 5};
    
    struct info info_test = fun_area_perimetr(circle_test);
    const struct info expected = {2 * M_PI * r, M_PI * r * r};
    if (info_test.perimeter == expected.perimeter && info_test.area == expected.area) 
        result = 1;
    else
        result = 0;

    ASSERT_EQUAL(1, result);
}


CTEST(fun_check_intersection, intersection_1)
{
    StructCircle circle_test_1 = {{0, 0}, 0.5};
    StructCircle circle_test_2 = {{1, 0}, 0.5};
    
    const int result = fun_check_intersection(circle_test_1, circle_test_2);
    const int expected = 1;

    ASSERT_EQUAL(expected, result);
}

CTEST(fun_check_intersection, intersection_2)
{
    StructCircle circle_test_1 = {{-10, -5.5}, 6};
    StructCircle circle_test_2 = {{-10, 5}, 5};
    
    const int result = fun_check_intersection(circle_test_1, circle_test_2);
    const int expected = 1;

    ASSERT_EQUAL(expected, result);
}

CTEST(fun_check_intersection, intersection_3)
{
    StructCircle circle_test_1 = {{-10, -5.5}, 5};
    StructCircle circle_test_2 = {{-10, 5}, 5};
    
    const int result = fun_check_intersection(circle_test_1, circle_test_2);
    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}