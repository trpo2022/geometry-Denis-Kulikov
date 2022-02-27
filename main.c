#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 10 // максимальное количество фигур
#define CIRCLE_WORD 7
#define LOWER_CASE 97
#define UPPER_CASE 66
#define COORDINATES_X_Y 2
#define MAX_ITERATION 7
#define FIGUR_CIRCLE 1
#define FIGUR_NO_CIRCLE 2
#define FIGUR_END 3
#define DOT 46
#define MINUS_SYM 45
#define NUMBER_0 48
#define LENGTH_ARG 100

struct circle {
    double point[COORDINATES_X_Y];
    double radius;
};

struct info {
    double perimeter;
    double area;
};

void fun_figur_check(int num, int* figur)
{
    char circle_name[] = {"circle"}, type_fig[CIRCLE_WORD];
    type_fig[CIRCLE_WORD - 1] = '\0';
    char symbol = 'a';
    int letter_count = 0, end = 0;
    type_fig[0] = 0;

    for (int j = 0; j < CIRCLE_WORD - 1; j++) {
        type_fig[j] = 0;
    }

    while (letter_count < CIRCLE_WORD - 1) {
        symbol = getchar();
        if (symbol == '\n') {
            end++;
            if (type_fig[0] != 0) {
                printf("Тип фигуры не распознан! Ожидаемый тип: 'circle'\n");
            }
            if (end == 2) {
                figur[num] = FIGUR_END;
                break;
            }
        } else {
            end = 0;
        }
        if (symbol >= LOWER_CASE && symbol <= LOWER_CASE + 25) {
            type_fig[letter_count] = symbol;
            letter_count++;
        }
        if (symbol >= UPPER_CASE && symbol <= UPPER_CASE + 25) {
            symbol += 'a' - 'A';
            type_fig[letter_count] = symbol;
            letter_count++;
        }
    }
    type_fig[letter_count] = '\0';

    for (letter_count = 0;
         letter_count < CIRCLE_WORD - 1 && type_fig != '\0' && figur[num] == 0;
         letter_count++) {
        if (type_fig[letter_count] != circle_name[letter_count]) {
            figur[num] = FIGUR_NO_CIRCLE;
            printf("%s", type_fig);
            printf("Тип фигуры не распознан! Ожидаемый тип: 'circle'\n");
            break;
        } else {
            figur[num] = FIGUR_CIRCLE;
        }
    }
}

void arg_del(char* arg, int length)
{
    for (int element = 0; element < length; element++)
        arg[element] = '\0';
}

struct circle fun_pos_cir()
{
    struct circle temp_cir;
    char symbol;
    int symbol_number = 0, count = 1, changes = 0, error = 0;
    int com[] = {0, 0, 0}, minus[] = {0, 0, 0};
    char arg[LENGTH_ARG];
    arg[LENGTH_ARG - 1] = '\0';

    symbol = getchar();
    if (symbol != '(') {
        printf("Ошибка: токены должны быть заключены в скобки!\n");
        error = 1;
    }

    symbol_number = 0;
    arg_del(arg, LENGTH_ARG);
    while (count == 1 && symbol_number < LENGTH_ARG) {
        symbol = getchar();
        if (symbol == DOT)
            com[count]++;
        if (symbol == MINUS_SYM)
            minus[count]++;
        if (symbol == DOT || symbol == MINUS_SYM
            || (symbol >= NUMBER_0 && symbol <= NUMBER_0 + 9)) {
            arg[symbol_number] = symbol;
            symbol_number++;
            changes++;
        } else if (changes != 0) {
            changes = -1;
        }
        if (changes == -1) {
            temp_cir.point[0] = atof(arg);
            if (com[count] > 1) {
                error = 1;
                printf("Ошибка в написании веществвенного числа!\n");
            }

            if (minus[count] > 1) {
                error = 1;
                printf("Ошибка: записан лишний минус!\n");
            }
            count++;
            changes = 0;
        }
    }

    symbol_number = 0;
    arg_del(arg, LENGTH_ARG);
    while (count == 2 && symbol_number < LENGTH_ARG) {
        symbol = getchar();
        if (symbol == DOT)
            com[count]++;
        if (symbol == MINUS_SYM)
            minus[count]++;
        if (symbol == DOT || symbol == MINUS_SYM
            || (symbol >= NUMBER_0 && symbol <= NUMBER_0 + 9)) {
            arg[symbol_number] = symbol;
            symbol_number++;
            changes++;
        } else if (changes != 0) {
            changes = -1;
        }
        if (changes == -1) {
            temp_cir.point[1] = atof(arg);
            if (com[count] > 1) {
                error = 1;
                printf("Ошибка в написании веществвенного числа!\n");
            }
            if (minus[count] > 1) {
                error = 1;
                printf("Ошибка: записан лишний минус!\n");
            }
            count++;
            changes = 0;
        }
    }

    symbol_number = 0;
    arg_del(arg, LENGTH_ARG);
    while (count == 3 && symbol_number < LENGTH_ARG) {
        symbol = getchar();
        if (symbol == DOT)
            com[count]++;
        if (symbol == MINUS_SYM)
            minus[count]++;
        if (symbol == DOT || symbol == MINUS_SYM
            || (symbol >= NUMBER_0 && symbol <= NUMBER_0 + 9)) {
            arg[symbol_number] = symbol;
            symbol_number++;
            changes++;
        } else if (changes != 0) {
            changes = -1;
        }
        if (changes == -1) {
            while (symbol == ' ') {
                symbol = getchar();
            }
            if (symbol != ')') {
                printf("Предупреждение: токены должны быть заключены в "
                       "скобки!\n");
            }
            temp_cir.radius = atof(arg);
            if (com[count] > 1) {
                error = 1;
                printf("Ошибка в написании веществвенного числа!\n");
            }
            if (minus[count] > 0) {
                error = 1;
                printf("Ошибка: отрицательный радиус!\n");
            }
            count++;
        }
    }
    if (error == 1)
        temp_cir.radius = 0;
    return temp_cir;
}

struct info fun_area_perimetr(struct circle cir)
{
    struct info number;
    number.perimeter = 2 * M_PI * cir.radius;
    number.area = M_PI * cir.radius * cir.radius;

    return number;
}

int fun_check_intersection(struct circle Acir, struct circle Bcir)
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
    int* figur = malloc(N * sizeof(int));
    int i, j, count_exit = 0, num = 0;

    struct circle circle_pos[N];
    struct info area_perimetr[N];

    printf("Уровень: Easy\nПравило ввода данных: тип(координата X, координата "
           "Y, радиус)\nПример: circle(1 2 3),\nОдна фигура занимает ровно "
           "одну строку.\n");
    printf("Пробельным символом может быть любой символом кроме: '.', '-' и "
           "цифр.\n\n");

    int info_intersection[N][N];
    for (int first_figur = 0; first_figur < N; first_figur++) {
        for (int second_figur = 0; second_figur < N; second_figur++) {
            info_intersection[first_figur][second_figur] = 0;
        }
    }

    while (count_exit != 1) {
        fun_figur_check(num, figur);
        if (figur[num] == FIGUR_NO_CIRCLE) {
            num--;
        }

        if (figur[num] == FIGUR_END) {
            count_exit = 1;
        }

        if (figur[num] == FIGUR_CIRCLE) {
            circle_pos[num] = fun_pos_cir();
            if (circle_pos[num].radius == 0)
                num--;
        }
        num++;
    }

    num--;

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
        printf("%d. circle(%.1f %.1f %.1f)\n\tperimeter = %f\n\tarea = "
               "%f\n\tintersects:\n",
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
