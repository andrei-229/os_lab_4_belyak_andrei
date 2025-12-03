#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

// Типы указателей на функции
typedef float (*SinIntegralFunc)(float, float, float);
typedef float (*SquareFunc)(float, float);

int main()
{
    void *library_handle = NULL;
    SinIntegralFunc SinIntegral = NULL;
    SquareFunc Square = NULL;

    int current_library = 1; // 1 = lib1.so, 2 = lib2.so

    printf("Программа 2: Динамическая загрузка библиотек\n");
    printf("Использует интерфейс dlopen/dlsym\n");
    printf("========================================\n");

    // Функция для загрузки библиотеки
    int load_library(int lib_number)
    {
        static void *libm_handle = NULL;
        if (!libm_handle)
        {
            libm_handle = dlopen("libm.so.6", RTLD_LAZY | RTLD_GLOBAL);
            if (!libm_handle)
            {
                fprintf(stderr, "Ошибка загрузки libm: %s\n", dlerror());
                return 0;
            }
        }
        // Закрываем предыдущую библиотеку
        if (library_handle != NULL)
        {
            dlclose(library_handle);
            library_handle = NULL;
        }

        // Формируем правильное имя файла
        char lib_name[20];
        if (lib_number == 1)
        {
            strcpy(lib_name, "./lib1.so");
        }
        else if (lib_number == 2)
        {
            strcpy(lib_name, "./lib2.so");
        }
        else
        {
            printf("Неверный номер библиотеки\n");
            return 0;
        }

        printf("Попытка загрузить библиотеку: %s\n", lib_name);

        // Загружаем библиотеку
        library_handle = dlopen(lib_name, RTLD_LAZY);
        if (!library_handle)
        {
            fprintf(stderr, "Ошибка dlopen: %s\n", dlerror());
            return 0;
        }

        // Сбрасываем ошибки
        dlerror();

        // Загружаем первую функцию
        SinIntegral = (SinIntegralFunc)dlsym(library_handle, "SinIntegral");
        char *error = dlerror();
        if (error != NULL)
        {
            fprintf(stderr, "Ошибка dlsym SinIntegral: %s\n", error);
            dlclose(library_handle);
            library_handle = NULL;
            return 0;
        }

        // Загружаем вторую функцию
        Square = (SquareFunc)dlsym(library_handle, "Square");
        error = dlerror();
        if (error != NULL)
        {
            fprintf(stderr, "Ошибка dlsym Square: %s\n", error);
            dlclose(library_handle);
            library_handle = NULL;
            return 0;
        }

        current_library = lib_number;
        printf("Успешно загружена библиотека %d\n", lib_number);
        if (lib_number == 1)
        {
            printf("Используется: метод прямоугольников + прямоугольник\n");
        }
        else
        {
            printf("Используется: метод трапеций + треугольник\n");
        }

        return 1;
    }

    // Начальная загрузка библиотеки
    if (!load_library(1))
    {
        fprintf(stderr, "Не удалось загрузить начальную библиотеку\n");
        return 1;
    }

    char input[256];
    printf("\nКоманды:\n");
    printf("  0 - переключить библиотеку\n");
    printf("  1 A B e - интеграл sin(x) на отрезке [A,B] с шагом e\n");
    printf("  2 A B - площадь фигуры со сторонами A и B\n");
    printf("  9 - выход\n");
    printf("> ");

    while (fgets(input, sizeof(input), stdin))
    {
        // Удаляем символ новой строки
        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0)
        {
            printf("> ");
            continue;
        }

        if (input[0] == '9')
        {
            printf("Выход из программы\n");
            break;
        }
        else if (input[0] == '0')
        {
            // Переключение библиотеки
            int new_lib = (current_library == 1) ? 2 : 1;
            if (!load_library(new_lib))
            {
                printf("Не удалось переключить библиотеку\n");
            }
        }
        else if (input[0] == '1')
        {
            if (SinIntegral == NULL)
            {
                printf("Ошибка: функция SinIntegral не загружена\n");
                printf("> ");
                continue;
            }

            float A, B, e;
            if (sscanf(input + 2, "%f %f %f", &A, &B, &e) == 3)
            {
                printf("Вычисление интеграла sin(x) на [%.4f, %.4f] с шагом %.6f...\n", A, B, e);
                float result = SinIntegral(A, B, e);
                printf("Результат: %.6f\n", result);
            }
            else
            {
                printf("Ошибка: неверные аргументы. Используйте: 1 A B e\n");
            }
        }
        else if (input[0] == '2')
        {
            if (Square == NULL)
            {
                printf("Ошибка: функция Square не загружена\n");
                printf("> ");
                continue;
            }

            float A, B;
            if (sscanf(input + 2, "%f %f", &A, &B) == 2)
            {
                printf("Вычисление площади фигуры со сторонами %.4f и %.4f...\n", A, B);
                float result = Square(A, B);
                printf("Результат: %.6f\n", result);
            }
            else
            {
                printf("Ошибка: неверные аргументы. Используйте: 2 A B\n");
            }
        }
        else
        {
            printf("Неизвестная команда\n");
        }

        printf("> ");
    }

    // Закрываем библиотеку перед выходом
    if (library_handle != NULL)
    {
        dlclose(library_handle);
    }

    return 0;
}