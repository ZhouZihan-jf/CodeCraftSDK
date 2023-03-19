//
// Created by 10259 on 2023/3/19.
//
#include "Position.h"


void Position::setPosition(float x, float y) {
    Position::x = x;
    Position::y = y;
}

float Position::getX() const {
    return x;
}

float Position::getY() const {
    return y;
}

Position::Position() {

}

Position::Position(float x, float y) {
    Position::x = x;
    Position::y = y;

}
