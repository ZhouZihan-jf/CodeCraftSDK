//
// Created by 10259 on 2023/3/19.
//
#include "Workshop.h"


int Workshop::getWorkType() const {
    return workType;
}

void Workshop::setWorkType(int workType) {
    Workshop::workType = workType;
}

const Position &Workshop::getPosition() const {
    return position;
}

void Workshop::setPosition(const Position &position) {
    Workshop::position = position;
}

int Workshop::getLeftProduceTime() const {
    return leftProduceTime;
}

void Workshop::setLeftProduceTime(int leftProduceTime) {
    Workshop::leftProduceTime = leftProduceTime;
}

int Workshop::getProductState() const {
    return productState;
}

void Workshop::setProductState(int productState) {
    Workshop::productState = productState;
}

int Workshop::getNumber() const {
    return number;
}

void Workshop::setNumber(int number) {
    Workshop::number = number;
}

const vector<int> &Workshop::getMaterialNum() const {
    return materialNum;
}

void Workshop::setMaterialNum(const vector<int> &materialNum) {
    Workshop::materialNum = materialNum;
}

Workshop::Workshop(int workType, const Position &position) {
    Workshop::workType = workType;
    Workshop::position = position;

}


Workshop::Workshop(){};

