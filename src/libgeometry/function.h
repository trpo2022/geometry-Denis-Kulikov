#pragma once

#include "struct.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMPARISON(FigurdEnter, FigurComparison, FigurLength, result) \
    {                                                                 \
        char* TempString = malloc((FigurLength + 1) * sizeof(char));  \
        strcpy(TempString, FigurdEnter);                              \
        TempString[FigurLength] = '\0';                               \
        result = !strcmp(TempString, FigurComparison);                \
        free(TempString);                                             \
    }
#define ERROR           \
    Circle.radius = -1; \
    return Circle;
#define SPACE                                            \
    for (int j = 0; j < num + L_CIRCLE + space + 1; j++) \
        printf(" ");

#define L_CIRCLE 6
#define L_MAX 100
#define COORDINATES_X_Y 2
#define MAX_ITERATION 7
