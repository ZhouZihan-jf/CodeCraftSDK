//
// Created by 10259 on 2023/3/19.
//
#include <cmath>
#include "LineSpeed.h"


void LineSpeed::setLineSpeed(double x, double y) {
    this->x = x;
    this->y = y;
}

double LineSpeed::getModule() const{
    double x = this->x;
    double y = this->y;

    return std::sqrt(pow(x,2) + pow(y,2));
}

LineSpeed::LineSpeed() {
}

LineSpeed::LineSpeed(double x, double y) {
    this->x = x;
    this->y = y;
}

