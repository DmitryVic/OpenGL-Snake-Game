cmake_minimum_required(VERSION 3.10)
project(SnakeGame)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)




# # Находим OpenGL
# find_package(OpenGL REQUIRED)

# Добавить исходники
add_executable(SnakeGame
    src/main.cpp
    src/snake.cpp
    src/Food.cpp
    src/randomGenerate.cpp
    )


# Линкуем библиотеки
# target_link_libraries(${PROJECT_NAME}
#     glew
#     glfw
# )

# Для Windows добавляем необходимые системные библиотеки
# if(WIN32)
#     target_link_libraries(${PROJECT_NAME}
#         opengl32
#         gdi32
#     )
# elseif(UNIX AND NOT APPLE)
#     # Для Linux
#     find_package(X11 REQUIRED)
#     find_package(OpenGL REQUIRED)
    
#     target_link_libraries(${PROJECT_NAME}
#         OpenGL::GL
#         X11
#         pthread
#         dl
#     )
# endif()

# # Явно указать include-директории для cppcheck
target_include_directories(SnakeGame PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# # Различия между Windows и Linux
if (WIN32)

    # Windows (MSYS2 MinGW) - СТАТИЧЕСКАЯ линковка
    message(STATUS "Windows: Using STATIC linking")
    
    set(GLEW_INCLUDE_DIR "C:/msys64/mingw64/include")
    set(GLFW_INCLUDE_DIR "C:/msys64/mingw64/include")
    
    # СТАТИЧЕСКИЕ библиотеки
    set(GLEW_STATIC_LIB "C:/msys64/mingw64/lib/libglew32.a")
    set(GLFW_STATIC_LIB "C:/msys64/mingw64/lib/libglfw3.a")
    
    include_directories(${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})
    
    target_link_libraries(SnakeGame
        ${GLEW_STATIC_LIB}  # Статическая GLEW
        ${GLFW_STATIC_LIB}  # Статическая GLFW
        opengl32
        gdi32
    )
    
    # Важно: определение для статической сборки GLEW
    target_compile_definitions(SnakeGame PRIVATE GLEW_STATIC)

    # # Windows (MSYS2 MinGW)
    # # ярлык установки мингв MSYS2 MINGW64 компилятор gcc выбирать тотже, библиотека установлена в C:/msys64/mingw64
    # set(GLEW_INCLUDE_DIR "C:/msys64/mingw64/include")
    # set(GLEW_LIBRARY "C:/msys64/mingw64/lib/libglew32.dll.a")

    # set(GLFW_INCLUDE_DIR "C:/msys64/mingw64/include")
    # set(GLFW_LIBRARY "C:/msys64/mingw64/lib/libglfw3.dll.a")

    # include_directories(${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})
    # link_directories("C:/msys64/mingw64/lib")

    # target_link_libraries(SnakeGame
    # ${GLEW_LIBRARY}
    # ${GLFW_LIBRARY}
    # opengl32
    # gdi32
    # )

else()
    # Linux
     # Linux - тоже СТАТИЧЕСКАЯ линковка
    message(STATUS "Linux: Using STATIC linking")
    
    find_package(OpenGL REQUIRED)
    
    # Ищем статические библиотеки
    find_library(GLEW_STATIC_LIB NAMES libGLEW.a GLEW PATHS /usr/lib /usr/local/lib)
    find_library(GLFW_STATIC_LIB NAMES libglfw3.a glfw3 PATHS /usr/lib /usr/local/lib)
    
    if(NOT GLEW_STATIC_LIB)
        message(FATAL_ERROR "Static GLEW library not found! Install libglew-dev")
    endif()
    
    if(NOT GLFW_STATIC_LIB)
        message(FATAL_ERROR "Static GLFW library not found! Install libglfw3-dev")
    endif()
    
    target_link_libraries(SnakeGame
        OpenGL::GL
        ${GLEW_STATIC_LIB}  # Статическая GLEW
        ${GLFW_STATIC_LIB}  # Статическая GLFW
        pthread
        dl
        X11
    )
    
    # Определение для статической сборки GLEW
    target_compile_definitions(SnakeGame PRIVATE GLEW_STATIC)
endif()


# # Автоматический запуск CppCheck ТОЛЬКО в Debug
# find_program(CPPCHECK cppcheck)
# if(CPPCHECK AND CMAKE_BUILD_TYPE STREQUAL "Debug")  # AND CMAKE_BUILD_TYPE STREQUAL "Debug" только в дебагере
#     add_custom_target(cppcheck ALL
#         COMMAND ${CPPCHECK}
#             --project=${CMAKE_BINARY_DIR}/compile_commands.json
#             --enable=warning,performance,portability,style
#             --suppress=missingIncludeSystem
#             --suppressions-list=${CMAKE_SOURCE_DIR}/.cppcheck-suppressions
#             --inline-suppr
#             --check-level=exhaustive
#         COMMENT "Запуск CppCheck (только в Debug-сборке)..."
#     )
# endif()