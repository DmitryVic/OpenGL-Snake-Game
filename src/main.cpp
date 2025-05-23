#include "randomGenerate.h"
#include "snake.h"
#include "Food.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath> // для sin и cos
#include <thread>    // Для std::this_thread   time
#include <chrono>    // Для std::chrono        time
// #include <cstdlib>
// #include <ctime>





int main() {
    
    using clock = std::chrono::steady_clock; // часы, которые гарантированно идут "вперёд" и не подвержены изменениям системного времени
    auto lastUpdateTime = clock::now(); //clock::now() возвращает текущее время с момента запуска часов ( время последнего обновления позиции змейки)
    const std::chrono::milliseconds updateInterval(100); // Скорость змейки: 10 обновлений/сек 

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

    Snake SNAKE;                                                    // Создали змейку

    Food* ptrFOOD = new Food(4.8f, 0.02f, randomGenGameBoard(), randomGenGameBoard());
    bool keyDontCount = false;                                      // Отрисовка медленее возможного нажатия и основного цикла, чтобы предотвратить изменения до отрисовки
    bool keyPressedLeft = false;                                    // Клавиша нажата? Если клавиша нажата, то больше ее не читаем пока не отожмем
    bool keyPressedRight = false;                                   // Клавиша нажата? Если клавиша нажата, то больше ее не читаем пока не отожмем
    bool keyPressedUp = false;                                      // Клавиша нажата? Если клавиша нажата, то больше ее не читаем пока не отожмем
    bool keyPressedDown = false;                                    // Клавиша нажата? Если клавиша нажата, то больше ее не читаем пока не отожмем
    
    /*
                ОСНОВНОЙ ЦИКЛ
    */
     while (!glfwWindowShouldClose(window)) {
        
        auto currentTime = clock::now();                            // Получает текущее время
        auto elapsedTime = currentTime - lastUpdateTime;            // Считает, сколько времени прошло с последнего обновления

        // Устанавливаем цвет фона
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);                               // очищаем буфер кадра а именно фон GL_COLOR_BUFFER_BIT очистить цветовой буфер 

        // Проверяем нажатия клавиш GLFW_PRESS 
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && SNAKE.Direct != Snake::Direction::RIGHT 
        && SNAKE.Direct != Snake::Direction::LEFT && !keyDontCount && !keyPressedLeft) {
            SNAKE.Direct = Snake::Direction::LEFT;
            keyDontCount = true;                                        // Отрисовка медленее возможного нажатия и основного цикла, чтобы предотвратить изменения до отрисовки
            keyPressedLeft = true;                                      // Если клавиша нажата, то больше ее не читаем пока не отожмем
        }
        else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && SNAKE.Direct != Snake::Direction::LEFT 
        && SNAKE.Direct != Snake::Direction::RIGHT && !keyDontCount && !keyPressedRight) {
            SNAKE.Direct = Snake::Direction::RIGHT;
            keyDontCount = true;                                         // Отрисовка медленее возможного нажатия и основного цикла, чтобы предотвратить изменения до отрисовки
            keyPressedRight = true;                                      // Если клавиша нажата, то больше ее не читаем пока не отожмем
        }
        else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && SNAKE.Direct != Snake::Direction::DOWN 
        && SNAKE.Direct != Snake::Direction::UP && !keyDontCount && !keyPressedUp) {
            SNAKE.Direct = Snake::Direction::UP;
            keyDontCount = true;                                         // Отрисовка медленее возможного нажатия и основного цикла, чтобы предотвратить изменения до отрисовки
            keyPressedUp = true;                                       // Если клавиша нажата, то больше ее не читаем пока не отожмем
        }
        else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && SNAKE.Direct != Snake::Direction::UP 
        && SNAKE.Direct != Snake::Direction::DOWN && !keyDontCount && !keyPressedDown) {
            SNAKE.Direct = Snake::Direction::DOWN;
            keyDontCount = true;                                         // Отрисовка медленее возможного нажатия и основного цикла, чтобы предотвратить изменения до отрисовки
            keyPressedDown = true;                                      // Если клавиша нажата, то больше ее не читаем пока не отожмем
        }
        
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE) {        // Если клавиша отжата, только тогда можно ее нажимать снова
            keyPressedLeft = false;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE) {        // Если клавиша отжата, только тогда можно ее нажимать снова
            keyPressedRight = false;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE) {          // Если клавиша отжата, только тогда можно ее нажимать снова
            keyPressedUp = false;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) {        // Если клавиша отжата, только тогда можно ее нажимать снова
            keyPressedDown = false;
        }

        // Проверяет, пора ли обновлять змейку Если прошло больше или равно 100 мс → змейка двигается
        if (elapsedTime >= updateInterval) {
            SNAKE.move();                                             // Обновляем позицию змейки
            keyDontCount = 0;                                        //  запрет кнопок снят после отрисовки
            lastUpdateTime = currentTime;                              // Обновляет lastUpdateTime, чтобы отсчёт начался заново
            if (SNAKE.gameOver())   
                break;
        }

        SNAKE.show();                               // отрисовка змейки
        // Если столкновение с едой (еда сьедена), новая позиция 
        if (SNAKE.foodAte(ptrFOOD))
        {
            ptrFOOD->setX(randomGenGameBoard());
            ptrFOOD->setY(randomGenGameBoard());
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
