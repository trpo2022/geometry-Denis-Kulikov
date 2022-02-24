#include <stdio.h>
#include <stdlib.h>

#define N 10 // максимальное количество фигур

struct circle {
    double point[2];
    double radius;
};

void fun_figur_check(int num, int* figur) // определение фигуры
{
    char circle_name[] = {"circle"}, type_fig[7];
    char symbol = 'a';
    int i = 0, end = 0;

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

int main()
{
    int* figur = malloc(N * sizeof(int));
    int count_exit = 0, num = 0;

    // struct circle circle_pos[N];

    while (count_exit != 1) {
        fun_figur_check(num, figur);
        if (figur[num] == 2) {
            num--;
        }

        if (figur[num] == 3) {
            count_exit = 1;
        }

        num++;
    }
    num--;

    for (int i = 0; i < num; i++) {
        printf("\n %d", figur[i]);
    }

    return 0;
}
