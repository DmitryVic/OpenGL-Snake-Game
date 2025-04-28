#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath> // для sin и cos



int main() {
    if (!glfwInit()) {
        std::cerr << "Не удалось инициализировать GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    GLFWwindow* window = glfwCreateWindow(1000, 800, "0 1 Квадрат", nullptr, nullptr);
    if (!window) {
        std::cerr << "Не удалось создать окно GLFW\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Не удалось инициализировать GLEW\n";
        return -1;
    }
    
    // Начальные координаты квадрата
    float x_offset = 0.0f; 
    float y_offset = 0.0f; 
    float move_speed = 0.01f; // скорость движения квадрата

     float angle = 0.0f; // угол вращения

     // Основной цикл
     while (!glfwWindowShouldClose(window)) {
         // Устанавливаем цвет фона
         glClearColor(0.1f, 0.1f, 0.1f, 1.0f); 
         glClear(GL_COLOR_BUFFER_BIT); // очищаем буфер кадра а именно фон GL_COLOR_BUFFER_BIT очистить цветовой буфер
         
                // Проверяем нажатия клавиш
                if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                    x_offset -= move_speed;
                }
                // glfwGetKey(window, клавиша) проверяет состояние определённой клавиши в данный момент
                //GLFW_PRESS — клавиша нажата (держится нажатой).
                //GLFW_RELEASE — клавиша отпущена.
                if (glfwGetKey(window/* указатель на окно выше GLFWwindow* window*/, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                    x_offset += move_speed;
                }
                if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
                    y_offset += move_speed;
                }
                if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
                    y_offset -= move_speed;
                }
                
        // Увеличиваем угол поворота
        angle += 0.9f;
        if (angle > 360.0f)
            angle = 0.0f;


        // Рисуем квадрат
        glBegin(GL_QUADS);
            glColor3f(0.0f, 0.7f, 0.7f);
            glVertex2f(-0.02f + x_offset, -0.02f + y_offset);
            glVertex2f( 0.02f + x_offset, -0.02f + y_offset);
            glVertex2f( 0.02f + x_offset,  0.02f + y_offset);
            glVertex2f(-0.02f + x_offset,  0.02f + y_offset);
        glEnd();

        // Рисуем линию
        glBegin(GL_LINES);
            glColor3f(0.7f, 0.2f, 0.4f); //  линия
            glVertex2f(-1.0f, 0.0f);
            glVertex2f(1.0f, 0.0f);
        glEnd();

        // Рисуем линию
        glBegin(GL_LINES);
            glColor3f(0.1f, 0.4f, 0.7f); //  линия
            glVertex2f(0.0f, 1.0f);
            glVertex2f(0.0f, -1.0f);
        glEnd();

        // Вращающаяся линия
        glPushMatrix();
        /*
        glPushMatrix() сохраняет текущую матрицу преобразований т .е. положение, поворот...
        OpenGL использует стек матриц, чтобы сохран  состояния для рисования объектов
        */
        glLoadIdentity();            // Сброс матрицы в единичную (ВАЖНО!)
        //единичная матрица - это матрица не оказывает никакого эффекта на объекты
        // чтобы избежать накопления эффектов предыдущих трансформаций
        // иначе другие трансформации будут накапливаться !!!!!!
        glRotatef(angle, 0.0f, 0.0f, 1.0f); // поворот плоскости
        glBegin(GL_LINES);
            glColor3f(1.0f, 0.5f, 0.2f); // Цвет вращающейся линии
            glVertex2f(-0.8f, 0.0f);
            glVertex2f( 0.8f, 0.0f);
        glEnd();
        glPopMatrix(); // восстанавливает последнюю сохранённую матрицу из стека

        // Рисуем замкнутую линию (контур квадрата)
        glBegin(GL_LINE_LOOP);
            glColor3f(0.8f, 0.8f, 0.8f); // контур
            glVertex2f(-0.5f, -0.5f);
            glVertex2f( 0.5f, -0.5f);
            glVertex2f( 0.5f,  0.5f);
            glVertex2f(-0.5f,  0.5f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window); // отрисованый буфер в изображение
    glfwTerminate(); // обрабатывает все ожидающие события
    return 0;
}
