#include "randomGenerate.h"
#include <iostream>
#include <random>


float randomGenGameBoard(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> distrib(0, 45); // 46 значений
    return -0.9f + distrib(gen) * 0.04f;
}