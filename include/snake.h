#pragma once
#include "vector"
#include "Food.h"

class Snake
{
private:
    struct Segment {
        float x, y;
    };
    std::vector<Segment> segments;               // Вектор сегментов змейки
    
    float moveStep = 0.04f;                      // Шаг кратен размеру квадрата

    public:
    Snake(/* args */);
    ~Snake();
    
    enum Direction {UP, DOWN, LEFT, RIGHT};
    Direction Direct = RIGHT;                    // Направление

    void show();                                 // отрисовка змейки
    void move();                                 // позиция змейки меняется не в такт с отрисовкой 
    bool foodAte(Food* ptrFood);                 // Проверка пересечения с едой
    void pushSegmentSnake();                    // Увеличить змейку
    bool gameOver() const;                      // проверка на столкновение
};


