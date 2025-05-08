cmake_minimum_required(VERSION 3.10)
project(OpenGLES_Emulation)

set(CMAKE_CXX_STANDARD 17)

# Генерация compile_commands.json для cppcheck
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#путь для генерации
set(CMAKE_EXPORT_COMPILE_COMMANDS_FILE "${CMAKE_SOURCE_DIR}/compile_commands.json")


# Находим OpenGL
find_package(OpenGL REQUIRED)

# Создаем исполняемый файл
add_executable(OpenGLES_Emulation src/main.cpp)

# Различия между Windows и Linux
if (WIN32)
    # Windows (MSYS2 MinGW)
    # ярлык установки мингв MSYS2 MINGW64 компилятор gcc выбирать тотже, библиотека установлена в C:/msys64/mingw64
    set(GLEW_INCLUDE_DIR "C:/msys64/mingw64/include")
    set(GLEW_LIBRARY "C:/msys64/mingw64/lib/libglew32.dll.a")

    set(GLFW_INCLUDE_DIR "C:/msys64/mingw64/include")
    set(GLFW_LIBRARY "C:/msys64/mingw64/lib/libglfw3.dll.a")

    include_directories(${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})
    link_directories("C:/msys64/mingw64/lib")

    target_link_libraries(OpenGLES_Emulation
        OpenGL::GL
        glfw3
        glew32
    )

else()
    # Linux
    find_package(GLEW REQUIRED)
    find_package(glfw3 REQUIRED)

    target_link_libraries(OpenGLES_Emulation
        OpenGL::GL
        GLEW::GLEW
        glfw
    )
endif()


# Автоматический запуск CppCheck ТОЛЬКО в Debug
find_program(CPPCHECK cppcheck)
if(CPPCHECK AND CMAKE_BUILD_TYPE STREQUAL "Debug")  # AND CMAKE_BUILD_TYPE STREQUAL "Debug" только в дебагере
    add_custom_target(cppcheck ALL
        COMMAND ${CPPCHECK}
            --project=${CMAKE_BINARY_DIR}/compile_commands.json
            --enable=warning,performance,portability,style
            --suppress=missingIncludeSystem
            --suppressions-list=${CMAKE_SOURCE_DIR}/.cppcheck-suppressions
            --inline-suppr
            --check-level=exhaustive
        COMMENT "Запуск CppCheck (только в Debug-сборке)..."
    )
endif()