//
// Created by 10259 on 2023/3/19.
//
#include <cmath>
#include "LineSpeed.h"


void LineSpeed::setLineSpeed(float x, float y) {
    this->x = x;
    this->y = y;
}

float LineSpeed::getModule() const{
    float x = this->x;
    float y = this->y;

    return std::sqrt(x*x + y*y);
}

