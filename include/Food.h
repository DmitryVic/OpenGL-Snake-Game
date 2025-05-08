#pragma once


class Food
{
private:
    float angle = 0.0f; // угол вращения
    float speed;
    float lineLength; // Длина линии 
    float x;
    float y;

public:
    Food(float speed, float lineLength, float x, float y) : speed(speed), lineLength(lineLength), x(x), y(y){}
    ~Food() = default;
    void show();
    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);
};


