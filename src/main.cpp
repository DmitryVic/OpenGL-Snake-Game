#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath> // для sin и cos
#include "snake.h"
#include "Food.h"
#include <thread>    // Для std::this_thread   time
#include <chrono>    // Для std::chrono        time
#include <cstdlib>
#include <ctime>


int main() {
    
    using clock = std::chrono::steady_clock; // часы, которые гарантированно идут "вперёд" и не подвержены изменениям системного времени
    auto lastUpdateTime = clock::now(); //clock::now() возвращает текущее время с момента запуска часов ( время последнего обновления позиции змейки)
    const std::chrono::milliseconds updateInterval(100); // Скорость змейки: 10 обновлений/сек 
    
    // Инициализация генератора случайных чисел
    std::srand(std::time(nullptr));

    if (!glfwInit()) {
        std::cerr << "Не удалось инициализировать GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Змейка", nullptr, nullptr);
    if (!window) {
        std::cerr << "Не удалось создать окно GLFW\n";
        glfwTerminate();
        return -1;
    }
    //Snake
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Не удалось инициализировать GLEW\n";
        return -1;
    }

    Snake SNAKE;

    // Генерация чисел
    float randX = -0.9f + static_cast<float>(std::rand()) / (RAND_MAX / 1.8f);
    float randY = -0.9f + static_cast<float>(std::rand()) / (RAND_MAX / 1.8f);

    Food* ptrFOOD = new Food(3.5f, 0.03f, randX, randY);

     // Основной цикл
     while (!glfwWindowShouldClose(window)) {
        
        auto currentTime = clock::now();                        // Получает текущее время
        auto elapsedTime = currentTime - lastUpdateTime;        // Считает, сколько времени прошло с последнего обновления

        // Устанавливаем цвет фона
         glClearColor(0.1f, 0.1f, 0.1f, 1.0f); 
         glClear(GL_COLOR_BUFFER_BIT);                          // очищаем буфер кадра а именно фон GL_COLOR_BUFFER_BIT очистить цветовой буфер

                // Проверяем нажатия клавиш
                if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                    if (SNAKE.Direct != Snake::Direction::RIGHT) // Запрещаю реверс
                        SNAKE.Direct = Snake::Direction::LEFT;
                }
                if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                    if (SNAKE.Direct != Snake::Direction::LEFT)
                        SNAKE.Direct = Snake::Direction::RIGHT;
                }
                if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
                    if (SNAKE.Direct != Snake::Direction::DOWN)
                        SNAKE.Direct = Snake::Direction::UP;
                }
                if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
                    if (SNAKE.Direct != Snake::Direction::UP)
                        SNAKE.Direct = Snake::Direction::DOWN;
                }
                


        // Проверяет, пора ли обновлять змейку Если прошло больше или равно 100 мс → змейка двигается
        if (elapsedTime >= updateInterval) {
            SNAKE.move();                           // Обновляем позицию змейки
            lastUpdateTime = currentTime;           // Обновляет lastUpdateTime, чтобы отсчёт начался заново
            if (SNAKE.gameOver())
                break;
        }

        SNAKE.show();                               // отрисовка змейки
        if (SNAKE.foodAte(ptrFOOD))
        {
            randX = -0.9f + static_cast<float>(std::rand()) / (RAND_MAX / 1.8f);
            randY = -0.9f + static_cast<float>(std::rand()) / (RAND_MAX / 1.8f);

            ptrFOOD->setX(randX);
            ptrFOOD->setY(randY);
        }
        
        ptrFOOD->show();
        
        
        // Рисуем замкнутую линию (контур квадрата)
        glBegin(GL_LINE_LOOP);
            glColor3f(0.8f, 0.8f, 0.8f); // контур
            glVertex2f(-0.92f, -0.92f);
            glVertex2f( 0.92f, -0.92f);
            glVertex2f( 0.92f,  0.92f);
            glVertex2f(-0.92f,  0.92f);
        glEnd();

        glfwSwapBuffers(window); // отрисованый буфер в изображение
        glfwPollEvents(); // обрабатывает все ожидающие события

        // Небольшая пауза, чтобы не нагружать CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //При пройгрыше пока что пауза
    glfwDestroyWindow(window); 
    glfwTerminate();
    delete ptrFOOD;
    return 0;
}
