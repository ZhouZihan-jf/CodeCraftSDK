//
// Created by 10259 on 2023/3/19.
//
#include "Position.h"


void Position::setPosition(double x, double y) {
    Position::x = x;
    Position::y = y;
}

double Position::getX() const {
    return x;
}

double Position::getY() const {
    return y;
}

Position::Position() {

}

Position::Position(double x, double y) {
    Position::x = x;
    Position::y = y;

}
