#include <stdio.h>
#include <stdlib.h>

#define N 10 // максимальное количество фигур
#define LENGTH_ARG 100

struct circle {
    double point[2];
    double radius;
};

struct info {
    double perimeter;
    double area;
};

void fun_figur_check(int num, int* figur) // определение фигуры
{
    char circle_name[] = {"circle"}, type_fig[7];
    type_fig[6] = '\0';
    char symbol = 'a';
    int i = 0, end = 0;
    type_fig[0] = 0;

    for (int j = 0; j < 6; j++) {
        type_fig[j] = 0;
    }

    while (i < 6) {
        symbol = getchar();
        if (symbol == '\n') {
            end++;
            if (type_fig[0] != 0) {
                printf("Тип фигуры не распознан! Ожидаемый тип: 'circle'\n");
            }
            if (end != 2)
                printf("Нажмите 'enter', что закончить, или продолжите вводить "
                       "данные.\n");
            if (end == 2) {
                figur[num] = 3;
                break;
            }
        } else {
            end = 0;
        }
        if (symbol >= 97 && symbol <= 122) {
            type_fig[i] = symbol;
            i++;
        }
        if (symbol >= 66 && symbol <= 90) {
            symbol += 'a' - 'A';
            type_fig[i] = symbol;
            i++;
        }
    }
    type_fig[i] = '\0';

    for (int j = 0; j < 6 && type_fig != '\0' && figur[num] == 0; j++) {
        if (type_fig[j] != circle_name[j]) {
            figur[num] = 2;
            printf("%s", type_fig);
            printf("Тип фигуры не распознан! Ожидаемый тип: 'circle'\n");
            break;
        } else {
            figur[num] = 1;
        }
    }
}

void arg_del(char* a, int l)
{
    for (int i = 0; i < l; i++)
        a[i] = '\0';
}

struct circle fun_pos_cir()
{
    struct circle temp_cir;
    char symbol;
    int j = 0, count = 1, changes = 0;
    int com[] = {0, 0, 0}, minus[] = {0, 0, 0};
    char arg[LENGTH_ARG];
    arg[LENGTH_ARG - 1] = '\0';

    symbol = getchar();
    if (symbol != '(') {
        printf("Ошибка: токены должны быть заключены в скобки!");
        return temp_cir;
    }

    j = 0;
    arg_del(arg, LENGTH_ARG);
    while (count == 1 && j < LENGTH_ARG) {
        symbol = getchar();
        if (symbol == 46)
            com[count]++;
        if (symbol == 45)
            minus[count]++;
        if (symbol == 45 || symbol == 46 || (symbol >= 48 && symbol <= 57)) {
            arg[j] = symbol;
            j++;
            changes++;
        } else if (changes != 0) {
            changes = -1;
        }
        if (changes == -1) {
            temp_cir.point[0] = atof(arg);
            if (com[count] > 1)
                printf("Ошибка в написании веществвенного числа!\n");
            if (minus[count] > 1)
                printf("Ошибка: записан лишний минус!\n");
            count++;
            changes = 0;
        }
    }

    j = 0;
    arg_del(arg, LENGTH_ARG);
    while (count == 2 && j < LENGTH_ARG) {
        symbol = getchar();
        if (symbol == 46)
            com[count]++;
        if (symbol == 45)
            minus[count]++;
        if (symbol == 45 || symbol == 46 || (symbol >= 48 && symbol <= 57)) {
            arg[j] = symbol;
            j++;
            changes++;
        } else if (changes != 0) {
            changes = -1;
        }
        if (changes == -1) {
            temp_cir.point[1] = atof(arg);
            if (com[count] > 1)
                printf("Ошибка в написании веществвенного числа!\n");
            if (minus[count] > 1)
                printf("Ошибка: записан лишний минус!\n");
            count++;
            changes = 0;
        }
    }

    j = 0;
    arg_del(arg, LENGTH_ARG);
    while (count == 3 && j < LENGTH_ARG) {
        symbol = getchar();
        if (symbol == 46)
            com[count]++;
        if (symbol == 45)
            minus[count]++;
        if (symbol == 45 || symbol == 46 || (symbol >= 48 && symbol <= 57)) {
            arg[j] = symbol;
            j++;
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
            if (com[count] > 1)
                printf("Ошибка в написании веществвенного числа!\n");
            if (minus[count] > 1)
                printf("Ошибка: отрицательный радиус!\n");
            return temp_cir;
        }
    }

    return temp_cir;
}

struct info fun_area_perimetr(struct circle cir)
{
    struct info number;
    number.perimeter = 2 * 3.14 * cir.radius;
    number.area = 3.14 * cir.radius * cir.radius;

    return number;
}

int main()
{
    int* figur = malloc(N * sizeof(int));
    int i, count_exit = 0, num = 0;

    struct circle circle_pos[N];
    struct info area_perimetr[N];

    while (count_exit != 1) {
        fun_figur_check(num, figur);
        if (figur[num] == 2) {
            num--;
        }

        if (figur[num] == 3) {
            count_exit = 1;
        }

        if (figur[num] == 1) {
            circle_pos[num] = fun_pos_cir();
        }
        num++;
    }
    num--;

    for (i = 0; i < num; i++) {
        area_perimetr[i] = fun_area_perimetr(circle_pos[i]);
    }

    for (i = 0; i < num; i++) {
        printf("\n%f  %f", area_perimetr[i].perimeter, area_perimetr[i].area);
    }

    return 0;
}
