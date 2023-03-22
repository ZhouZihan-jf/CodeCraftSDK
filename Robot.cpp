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

double Robot::getTimeWorth() const {
    return timeWorth;
}

void Robot::setTimeWorth(double timeWorth) {
    Robot::timeWorth = timeWorth;
}

double Robot::getCollisionWorth() const {
    return collisionWorth;
}

void Robot::setCollisionWorth(double collisionWorth) {
    Robot::collisionWorth = collisionWorth;
}

double Robot::getRotate() const {
    return rotate;
}

void Robot::setRotate(double rotate) {
    Robot::rotate = rotate;
}

const LineSpeed &Robot::getLineSpeed() const {
    return lineSpeed;
}

void Robot::setLineSpeed(const LineSpeed &lineSpeed) {
    Robot::lineSpeed = lineSpeed;
}

double Robot::getToward() const {
    return toward;
}

void Robot::setToward(double toward) {
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

void Robot::set_frameid(int frameid) {
    Robot::frameid = frameid;
}

int Robot::get_frameid() const {
    return frameid;
}

Robot::Robot(){}

Robot::~Robot() = default;;
