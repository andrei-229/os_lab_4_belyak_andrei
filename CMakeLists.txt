cmake_minimum_required(VERSION 3.10)
project(lab4)

# Важно: отключаем все автоматические префиксы и суффиксы
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Полностью отключаем создание симлинков
set(CMAKE_SKIP_BUILD_RPATH TRUE)

# Собираем ВСЕ в одну директорию
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Не создавать версионированные библиотеки
set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
set(CMAKE_SHARED_MODULE_SUFFIX ".so")

include_directories(${CMAKE_SOURCE_DIR}/include)

# Флаги компиляции
if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -fPIC")
endif()

# Находим библиотеку dl
find_library(DL_LIBRARY dl)
if(DL_LIBRARY)
    message(STATUS "Найдена библиотека dl: ${DL_LIBRARY}")
endif()

# Создаем библиотеку 1 - ВАЖНО: не используем префикс "lib" в имени цели
add_library(lib1_dynamic SHARED src/lib1.c)
# Явно задаем имя выходного файла без префикса
set_target_properties(lib1_dynamic PROPERTIES
    OUTPUT_NAME "lib1"
    PREFIX ""
    SUFFIX ".so"
)

# Создаем библиотеку 2
add_library(lib2_dynamic SHARED src/lib2.c)
set_target_properties(lib2_dynamic PROPERTIES
    OUTPUT_NAME "lib2"
    PREFIX ""
    SUFFIX ".so"
)

# Программа 1: статическая линковка
add_executable(program1 src/program1.c)
target_link_libraries(program1 lib1_dynamic m)
set_target_properties(program1 PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "$ORIGIN"
)

# Программа 2: динамическая загрузка
add_executable(program2 src/program2.c)
if(DL_LIBRARY)
    target_link_libraries(program2 ${DL_LIBRARY})
endif()

message(STATUS "Сборка настроена для WSL")