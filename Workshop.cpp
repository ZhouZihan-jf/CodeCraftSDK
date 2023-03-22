//
// Created by 10259 on 2023/3/19.
//
#include "Workshop.h"
#include "type_workshop.h"

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

Workshop::Workshop(int workType, const Position &position, const vector<int> &needMaterialNum){
    Workshop::workType = workType;
    Workshop::position = position;
    Workshop::needMaterialNum = needMaterialNum;
}

Workshop::Workshop(){}

const vector<int> &Workshop::getNeedMaterialNum() const {
    return needMaterialNum;
}

Workshop::Workshop(int workType, const vector<int> &needMaterialNum) {
    Workshop::workType = workType;
    Workshop::needMaterialNum = needMaterialNum;
}

Workshop::Workshop(int workType, const Position &position) {
    Workshop::workType = workType;
    Workshop::position = position;
}

Workshop::Workshop(int workType) {
    Workshop::workType = workType;
}

void Workshop::setNeedMaterialNum(int workType) {
    vector<int> vec;
    vec.reserve(10);

    if(workType <= 3) {
        this->needMaterialNum = {0};
    }if(workType == 4){
        vec.push_back(1);
        vec.push_back(2);
        this->needMaterialNum = vec;
    } else if(workType == 5){
        vec.push_back(1);
        vec.push_back(3);
        this->needMaterialNum = vec;
    } else if(workType == 6){
        vec.push_back(2);
        vec.push_back(3);
        this->needMaterialNum = vec;
    } else if(workType ==7){
        vec.push_back(4);
        vec.push_back(5);
        vec.push_back(6);
        this->needMaterialNum = vec;
    } else if(workType == 8){
        vec.push_back(7);
        this->needMaterialNum = vec;
    } else if(workType == 9){
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
        vec.push_back(4);
        vec.push_back(5);
        vec.push_back(6);
        vec.push_back(7);
        this->needMaterialNum = vec;
    }

    vec.~vector();
}

Workshop::~Workshop() = default;

void Workshop::set_type(type_workshop typeWorkshop1)
{
    typeWorkshop = typeWorkshop1;
}

const type_workshop &Workshop::get_type() const
{
    return typeWorkshop;
}

int Workshop::set_type_workshop(int workType,int itemtype)//为判断机器人所带的物品与工作台类型显示的所需物品类型一致性
{
   typeWorkshop.set_type_workshop(workType);
   return typeWorkshop.get_state_workshop(itemtype);
}