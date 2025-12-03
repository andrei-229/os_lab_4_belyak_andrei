#include <math.h>
#include <stdio.h>
#include "../include/contract.h"

// Метод прямоугольников для интеграла sin(x)
float SinIntegral(float A, float B, float e)
{
    if (e <= 0.0f)
    {
        printf("[lib1] Ошибка: шаг должен быть положительным\n");
        return 0.0f;
    }

    // Если A > B, меняем местами
    if (A > B)
    {
        float temp = A;
        A = B;
        B = temp;
    }

    float integral = 0.0f;
    float x = A;
    int steps = (int)((B - A) / e);

    // Метод средних прямоугольников
    for (int i = 0; i < steps; i++)
    {
        float midpoint = x + e / 2.0f;
        integral += sin(midpoint) * e; // Используем sin вместо sinf
        x += e;
    }

    // Обработка остатка
    if (x < B)
    {
        float midpoint = x + (B - x) / 2.0f;
        integral += sin(midpoint) * (B - x);
    }

    printf("[lib1] Метод прямоугольников, шаг: %.6f\n", e);
    return integral;
}

// Площадь прямоугольника
float Square(float A, float B)
{
    if (A <= 0.0f || B <= 0.0f)
    {
        printf("[lib1] Ошибка: стороны должны быть положительными\n");
        return 0.0f;
    }

    printf("[lib1] Фигура: прямоугольник\n");
    return A * B;
}