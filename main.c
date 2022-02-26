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
            // if (end != 2)
            //     printf("Нажмите 'enter', чтобы закончить, или продолжите вводить "
            //            "данные.\n");
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
    int j = 0, count = 1, changes = 0, error = 0;
    int com[] = {0, 0, 0}, minus[] = {0, 0, 0};
    char arg[LENGTH_ARG];
    arg[LENGTH_ARG - 1] = '\0';

    symbol = getchar();
    if (symbol != '(') {
        printf("Ошибка: токены должны быть заключены в скобки!");
        temp_cir.radius = 0;
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
            if (com[count] > 1){
                error = 1;
                printf("Ошибка в написании веществвенного числа!\n");
            }
                
            if (minus[count] > 1){
                error = 1;
                printf("Ошибка: записан лишний минус!\n");
            }
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
            if (com[count] > 1){
                error = 1;
                printf("Ошибка в написании веществвенного числа!\n");
            }
            if (minus[count] > 1){
                error = 1;
                printf("Ошибка: записан лишний минус!\n");
            }
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
                printf("Ошибка: токены должны быть заключены в "
                       "скобки!\n");
            }
            temp_cir.radius = atof(arg);
            if (com[count] > 1){
                error = 1;
                printf("Ошибка в написании веществвенного числа!\n");
            }
            if (minus[count] > 0){
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
    number.perimeter = 2 * 3.14 * cir.radius;
    number.area = 3.14 * cir.radius * cir.radius;

    return number;
}

int fun_check_intersection(struct circle Acir, struct circle Bcir)
{
    double temp,
            a
            = (Acir.point[0] - Bcir.point[0]) * (Acir.point[0] - Bcir.point[0])
            + (Acir.point[1] - Bcir.point[1]) * (Acir.point[1] - Bcir.point[1]);
    temp = a;
    if (temp != 0) {
        for (int i = 0; i < 7; i++)
            a = (a + temp / a) / 2;
    }

    if (a <= Acir.radius + Bcir.radius) {
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

    printf("Уровень: Easy\nПравило ввода данных: тип(координата X, координата Y, радиус)\nПример: circle(1 2 3),\nОдна фигура занимает ровно одну строку.\n");
    printf("Пробельных символов может быть любым символом кроме: '.', '-' и цифр.\n\n");

    int info_intersection[N][N];
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            info_intersection[i][j] = 0;
        }
    }

    while (count_exit != 1) {
        fun_figur_check(num, figur);
        if (figur[num] == 2) {
            num--;
        }

        if (figur[num] == 3) {
            count_exit = 1;
        }

        if (figur[num] == 1) 
            circle_pos[num] = fun_pos_cir();
        if (circle_pos[num].radius == 0)
                num--;
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

    i = getchar();

    return 0;
}
