//
// Created by 10259 on 2023/3/19.
//
#include "Robot.h"


int Robot::getWorkshopId() const {
    return workshopId;
}

void Robot::setWorkshopId(int workshopId) {
    Robot::workshopId = workshopId;
}

int Robot::getItemType() const {
    return itemType;
}

void Robot::setItemType(int itemType) {
    Robot::itemType = itemType;
}

float Robot::getTimeWorth() const {
    return timeWorth;
}

void Robot::setTimeWorth(float timeWorth) {
    Robot::timeWorth = timeWorth;
}

float Robot::getCollisionWorth() const {
    return collisionWorth;
}

void Robot::setCollisionWorth(float collisionWorth) {
    Robot::collisionWorth = collisionWorth;
}

float Robot::getRotate() const {
    return rotate;
}

void Robot::setRotate(float rotate) {
    Robot::rotate = rotate;
}

const LineSpeed &Robot::getLineSpeed() const {
    return lineSpeed;
}

void Robot::setLineSpeed(const LineSpeed &lineSpeed) {
    Robot::lineSpeed = lineSpeed;
}

float Robot::getToward() const {
    return toward;
}

void Robot::setToward(float toward) {
    Robot::toward = toward;
}

const Position &Robot::getPosition() const {
    return position;
}

void Robot::setPosition(const Position &position) {
    Robot::position = position;
}

Robot::Robot(const Position &position) {
    Robot::position = position;
}

Robot::Robot(){};
