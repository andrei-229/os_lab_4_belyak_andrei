#include <math.h>
#include <stdio.h>
#include "../include/contract.h"

// Метод трапеций для интеграла sin(x)
float SinIntegral(float A, float B, float e)
{
    if (e <= 0.0f)
    {
        printf("[lib2] Ошибка: шаг должен быть положительным\n");
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

    // Метод трапеций
    for (int i = 0; i < steps; i++)
    {
        float left = sin(x); // Используем sin вместо sinf для совместимости
        float right = sin(x + e);
        integral += (left + right) * e / 2.0f;
        x += e;
    }

    // Обработка остатка
    if (x < B)
    {
        float left = sin(x);
        float right = sin(B);
        integral += (left + right) * (B - x) / 2.0f;
    }

    printf("[lib2] Метод трапеций, шаг: %.6f\n", e);
    return integral;
}

// Площадь прямоугольного треугольника
float Square(float A, float B)
{
    if (A <= 0.0f || B <= 0.0f)
    {
        printf("[lib2] Ошибка: стороны должны быть положительными\n");
        return 0.0f;
    }

    printf("[lib2] Фигура: прямоугольный треугольник\n");
    return (A * B) / 2.0f;
}