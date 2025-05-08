#include "Food.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


void Food::show(){
    
    // Увеличиваем угол поворота
    angle += speed;
    if (angle > 360.0f)
        angle = 0.0f;

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
    glTranslatef(x, y, 0.0f); 

    // Вращаем вокруг оси Z (для 2D)
    glRotatef(angle, 0.0f, 0.0f, 1.0f);

    // Устанавливаем толщину линии (по умолчанию 1.0)
    glLineWidth(3.0f);

    glBegin(GL_LINES);
        glColor3f(1.0f, 0.5f, 0.2f); // Цвет вращающейся линии
        glVertex2f(-lineLength/2, -lineLength/2); // Начало линии
        glVertex2f( lineLength/2,  lineLength/2); // Конец линии
    glEnd();

    glBegin(GL_LINES);
        glColor3f(0.2f, 0.5f, 1.0f); // Цвет вращающейся линии
        glVertex2f(lineLength/2, -lineLength/2); // Начало линии
        glVertex2f( -lineLength/2,  lineLength/2); // Конец линии
    glEnd();

    glPopMatrix(); // восстанавливает последнюю сохранённую матрицу из стека
}

float Food::getX() const{
    return this->x;
}

float Food::getY() const{
    return this->y;
}


//Добавить защиту на добавление не верных значений
void Food::setY(float y){
    this->y = y;
}

//Добавить защиту на добавление не верных значений
void Food::setX(float x){
    this->x = x;
}