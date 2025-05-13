#include "snake.h"
#include "Food.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <bits/stdc++.h>



Snake::Snake(/* args */)
{
    // Начальные позиции двух сегментов
    segments.push_back({-0.9f, 0.9f});   // Голова
    segments.push_back({-0.9f, 0.9f}); // Хвост
}

Snake::~Snake()
{
}



void Snake::show(){

    // Отрисовка всех сегментов
    for (const auto& segment : segments) {
        glBegin(GL_QUADS);
        //glColor3f(0.2f, 0.8f, 0.8f);
        glColor3f(sin(segment.x) * sin(segment.x) + 0.5f, segment.x * segment.x * 1.2f + 0.4f, (segment.x + segment.y)*(segment.x + segment.y) + 0.5f);
        
        glVertex2f(-0.02f + segment.x, -0.02f + segment.y);
        glVertex2f(0.02f + segment.x, -0.02f + segment.y);
        glVertex2f( 0.02f + segment.x, 0.02f + segment.y);
        glVertex2f(-0.02f + segment.x,  0.02f + segment.y);
        glEnd();
    }
}

void Snake::move(){
    // Сначала перемещаем все сегменты (кроме головы)
    for (int i = segments.size() - 1; i > 0; --i) {
        segments[i].x = segments[i-1].x;
        segments[i].y = segments[i-1].y;
    }

    // перемещаем голову
    switch (Direct) {
        case UP:    segments[0].y += moveStep; break;
        case DOWN:  segments[0].y -= moveStep; break;
        case LEFT:  segments[0].x -= moveStep; break;
        case RIGHT: segments[0].x += moveStep; break;
    }

    // Проверка границ для головы
    if (segments[0].x < -0.92f) segments[0].x = 0.9f;
    if (segments[0].x > 0.92f)  segments[0].x = -0.9f;
    if (segments[0].y > 0.92f)  segments[0].y = -0.9f;
    if (segments[0].y < -0.92f) segments[0].y = 0.9f;
}

bool Snake::foodAte(Food* ptrFood){
    float x = ptrFood->getX();
    float y = ptrFood->getY();
    //задаем точность, с которой будут сравниваться числа
    float epsilon = 0.02f;
    //ищем разницу между числами
    float diffX = x - segments[0].x;
    float diffY = y - segments[0].y;
    //если разница между числами не превышает epsilon (-epsilon < diff < epsilon), будем считать их равными
    bool equalX = (diffX < epsilon) && (-diffX < epsilon);
    bool equalY = (diffY < epsilon) && (-diffY < epsilon);

    if (equalX && equalY){
        pushSegmentSnake();
        return true;
    }
    return false;
}

void Snake::pushSegmentSnake(){
    unsigned int segmentsSize = segments.size();
    segments.push_back({segments[segmentsSize - 1].x, segments[segmentsSize - 1].y}); // Дбавляем = последнему потом вытянится ненадо дорисовывать , а если из-за этого будет столкновение
}

bool Snake::gameOver() const {
    const float epsilon = 0.001f;
    const Segment& head = segments[0];

    // Проверяем только голову против остальных сегментов
    for (size_t i = 3; i < segments.size(); ++i) { // Начиная с 3-го, чтобы игнорировать первые 2
        const auto& seg = segments[i];
        
        bool x_match = std::abs(head.x - seg.x) < epsilon;
        bool y_match = std::abs(head.y - seg.y) < epsilon;
        
        if (x_match && y_match) {
            return true;
        }
    }
    return false;
}