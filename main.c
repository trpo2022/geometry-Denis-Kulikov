#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define COMPARISON(FigurdEnter, FigurComparison, FigurLength, result)\
    {\
        char* TempString = malloc((FigurLength + 1) * sizeof(char));\
        strcpy(TempString, FigurdEnter);\
        TempString[FigurLength] = '\0';\
        result = !strcmp(TempString, FigurComparison);\
        free(TempString);\
    }

#define N 10 // максимальное количество фигур
#define L_CIRCLE 6
#define L_MAX 50
#define COORDINATES_X_Y 2
#define MAX_ITERATION 7


typedef struct FigurCircle {
    double point[COORDINATES_X_Y];
    double radius;
} StructCircle;

struct info {
    double perimeter;
    double area;
};


StructCircle InputArg() {
    StructCircle Circle;
    int num = 0, Arg = 0, Space = 0, ArgCoutn[] = {0, 0, 0}, IsMinus[] = {0, 0, 0}, IsDot[] = {0, 0, 0};
    int Unfinished = 0, MinusError = 0, DotError = 0, VoidArgError = 0;
    char input = getchar();
    char Buffer[L_MAX];
    for (int i = 0; i < L_MAX; i++)
        Buffer[i] = 0;
    while (input != ')')
    {
        if (input == ')' &&  !ArgCoutn[2]) 
            Unfinished++;
        if (input == ' ')
            Space++;
        if (input != ' '){
            if(input == '-') {
                if((IsMinus[Arg] || ArgCoutn[Arg]) && Arg != 2){ 
                    MinusError++;
                    for(int i = 0; i < num + L_CIRCLE + 2 + Space; i++){
                        printf(" ");
                    }
                    printf("^ неправильное использование минуса!\n");
                    Circle.radius = -1;
                    while(getchar() != '\n');
                    return Circle;
                }
                if (Arg == 2) {
                    MinusError++;
                    for(int i = 0; i < num + L_CIRCLE + 2 + Space; i++){
                        printf(" ");
                    }
                    printf("^ радиус не может быть отрицательным\n");
                    Circle.radius = -1;
                    while(getchar() != '\n');
                    return Circle;
                }
                IsMinus[Arg]++;
            } else if(input == '.') {
                if(IsDot[Arg]){
                    DotError++;
                    for(int i = 0; i < num + L_CIRCLE + 2 + Space; i++){
                        printf(" ");
                    }
                    printf("^ неправильное использование точки!\n");
                    Circle.radius = -1;
                    while(getchar() != '\n');
                    return Circle;
                }
                Buffer[num] = '.';
                IsDot[Arg]++;
                num++;
            } else if(input == ',') {
                if (ArgCoutn[Arg]) {
                    Buffer[num] = ' ';
                    Arg++;
                    if (Arg > 2) {
                        for(int i = 0; i < num + L_CIRCLE + 2 + Space; i++){
                            printf(" ");
                        }
                        printf("^ Лишний токен\n");
                        Circle.radius = -1;
                        while(getchar() != '\n');
                        return Circle;
                    }
                } else {
                    VoidArgError++;
                    for(int i = 0; i < num + L_CIRCLE + 2 + Space; i++){
                        printf(" ");
                    }
                    printf("^ Пустой аргумент!\n");
                    Circle.radius = -1;
                    while(getchar() != '\n');
                    return Circle;
                }
                num++;
            } else if(isdigit(input)) {
                ArgCoutn[Arg]++;
                Buffer[num] = input;
                num++;
            } else {
                if (input == '\n') {
                    for(int i = 0; i < num + L_CIRCLE + 2 + Space; i++){
                        printf(" ");
                    }
                    printf("^ Пустой токен!\n");
                    Circle.radius = -1;
                    return Circle;
                }
                printf("Неверно введены аргументы!\n");
                Circle.radius = -1;
                while(getchar() != '\n');
                return Circle;
            }
        }
        input = getchar();
    }
    if(input == ')') {
        while(getchar() != '\n');
        if (!MinusError && !DotError && !VoidArgError && Arg == 2) {
            char *YValue, *RadValue;
            Circle.point[0] = strtod (Buffer, &YValue);
            if (IsMinus[0])
                Circle.point[0] *= -1;
            Circle.point[1] = strtod (YValue, &RadValue);
            if (IsMinus[1])
                Circle.point[1] *= -1;
            Circle.radius = strtod (RadValue, NULL);
            return Circle;
        } else {
            printf("Параметры введены не верно.\n");
            Circle.radius = -1;
            return Circle;
        }
    }
    Circle.radius = -1;
    return Circle;
}

StructCircle InputInfo()
{
    StructCircle Circle;
    char FigurCircle[] = "circle", FigurEnter[L_MAX], Answer = 0;
    int IsCircle;
    
    int num = -1, SpaceError = 0, FatalError = 0;
    do {
        num++;
        FigurEnter[num] = getchar();
        COMPARISON(FigurEnter, FigurCircle, L_CIRCLE, IsCircle);
        if (FigurEnter[num] == '\n' && num > 0) {
            printf("Неправильно введена фигура.\n");
            Circle.radius = -1;
            return Circle;
        }
        if (num > L_CIRCLE ) {
            while (FigurEnter[num] != '\n')
                FigurEnter[num] = getchar();
            printf("Неправильно введена фигура.\n");
            Circle.radius = -1;
            return Circle;
        }
        if (FigurEnter[num] == '\n' && num == 0) {
            do{
                printf("Хотите закончить ввод данных? y/n \n");
                Answer = getchar();
                if (Answer != 'y' && Answer != 'Y' && Answer != 'n' && Answer != 'N') {
                    while (getchar() != '\n');
                }
            } while (Answer != 'y' && Answer != 'Y' && Answer != 'n' && Answer != 'N');
            Answer = tolower(Answer);
            getchar();
            if (Answer == 'y'){
                printf("Конец ввода.\n");
                Circle.radius = -2;
                return Circle;
            }
            num = -1;
        }        
        if (IsCircle && FigurEnter[num] != '(' && num >= L_CIRCLE) {
            if (IsCircle && FigurEnter[num] == ' ') {
                SpaceError++;
                num--;
            } else {
                FatalError++;
            }
        }
        if (FigurEnter[num] == '(')
            break;
    } while (FigurEnter[num] != '(' && num < L_MAX);
    if (IsCircle) {
        if (SpaceError) 
            printf("       ^Лишний отступ перед аргументами.\n");
        if(FatalError)
            printf("Фигура не распознана. Ожидается: %s\n", FigurCircle);
        if (SpaceError || FatalError) {
            Circle.radius = -1;
            return Circle;
        } 
        if (!SpaceError && !FatalError) 
            return Circle = InputArg(Circle);
    }

    Circle.radius = -1;
    return  Circle;
}

void arg_del(char* arg, int length)
{
    for (int element = 0; element < length; element++)
        arg[element] = '\0';
}

struct info fun_area_perimetr(StructCircle cir)
{
    struct info number;
    number.perimeter = 2 * M_PI * cir.radius;
    number.area = M_PI * cir.radius * cir.radius;

    return number;
}

int fun_check_intersection(StructCircle  Acir, StructCircle Bcir)
{
    double temp,
            distance
            = (Acir.point[0] - Bcir.point[0]) * (Acir.point[0] - Bcir.point[0])
            + (Acir.point[1] - Bcir.point[1]) * (Acir.point[1] - Bcir.point[1]);
    temp = distance;
    if (temp != 0) {
        for (int iteration = 0; iteration < MAX_ITERATION; iteration++)
            distance = (distance + temp / distance) / 2;
    }

    if (distance <= Acir.radius + Bcir.radius) {
        return 1;
    }
    return 0;
}

int main()
{
    int i, j, num;
    StructCircle circle_pos[N];
    struct info area_perimetr[N];

    printf("Уровень: Easy\nПравило ввода данных: тип(координата X, координата "
           "Y, радиус)\nПример: circle(1, 2, 3)\nОдна фигура занимает ровно "
           "одну строку\n"
           "Чтобы завершить ввод нажмите ещё раз enter после ввода данных\n");

    int info_intersection[N][N];
    for (int first_figur = 0; first_figur < N; first_figur++) {
        for (int second_figur = 0; second_figur < N; second_figur++) {
            info_intersection[first_figur][second_figur] = 0;
        }
    }
    
    for (i = 0; i < N; i++) {
        circle_pos[i] = InputInfo();
        if (circle_pos[i].radius == -2) {
            num = i;
            break;
        }
        if (circle_pos[i].radius == -1)
            i--;
        if (i == N -1)
            num = i;
    }

    for (i = 0; i < num; i++) {
        for (j = 0; j < num; j++) {
            if (i == j) {
                j++;
                if (j == num)
                    break;
            }
            info_intersection[i][j]
                    = fun_check_intersection(circle_pos[i], circle_pos[j]);
        }
    }

    for (i = 0; i < num; i++) {
        area_perimetr[i] = fun_area_perimetr(circle_pos[i]);
    }

    for (i = 0; i < num; i++) {
        printf("%d. circle(%.2f %.2f %.2f)\n\tperimeter = %.3f\n\tarea = "
               "%.3f\n\tintersects:\n",
               i + 1,
               circle_pos[i].point[0],
               circle_pos[i].point[1],
               circle_pos[i].radius,
               area_perimetr[i].perimeter,
               area_perimetr[i].area);
        for (j = 0; j < num; j++) {
            if (i == j) {
                j++;
                if (j == num)
                    break;
            }
            if (info_intersection[i][j] == 1)
                printf("\t   %d. circle\n", j + 1);
        }
        printf("\n");
    }
    return 0;
}