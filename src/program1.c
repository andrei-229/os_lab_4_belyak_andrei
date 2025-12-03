#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/contract.h"

void print_help()
{
    printf("\nКоманды:\n");
    printf("  0              - выход из программы\n");
    printf("  1 A B e        - интеграл sin(x) на отрезке [A, B] с шагом e\n");
    printf("  2 A B          - площадь фигуры со сторонами A и B\n");
    printf("\nПримеры:\n");
    printf("  1 0 3.14159 0.001  - интеграл от 0 до pi\n");
    printf("  2 5 10             - площадь фигуры со сторонами 5 и 10\n");
    printf("\n> ");
}

int main()
{
    char input[256];

    printf("========================================\n");
    printf("Программа 1: Статическая линковка\n");
    printf("Используется lib1.so (прямоугольники + прямоугольник)\n");
    printf("========================================\n");

    print_help();

    while (1)
    {
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        // Удаляем символ новой строки
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0)
        {
            printf("> ");
            continue;
        }

        if (input[0] == '0')
        {
            printf("Выход из программы.\n");
            break;
        }
        else if (input[0] == '1')
        {
            float A, B, e;
            if (sscanf(input + 2, "%f %f %f", &A, &B, &e) == 3)
            {
                printf("Вычисление интеграла sin(x) от %.4f до %.4f с шагом %.6f...\n", A, B, e);
                float result = SinIntegral(A, B, e);
                printf("Результат: %.8f\n", result);
            }
            else
            {
                printf("Ошибка: неверные аргументы. Формат: 1 A B e\n");
                printf("Пример: 1 0 3.14159 0.001\n");
            }
        }
        else if (input[0] == '2')
        {
            float A, B;
            if (sscanf(input + 2, "%f %f", &A, &B) == 2)
            {
                printf("Вычисление площади фигуры со сторонами %.4f и %.4f...\n", A, B);
                float result = Square(A, B);
                printf("Результат: %.8f\n", result);
            }
            else
            {
                printf("Ошибка: неверные аргументы. Формат: 2 A B\n");
                printf("Пример: 2 5 10\n");
            }
        }
        else
        {
            printf("Неизвестная команда. Доступные команды: 0, 1, 2\n");
        }

        printf("\n> ");
    }

    return 0;
}