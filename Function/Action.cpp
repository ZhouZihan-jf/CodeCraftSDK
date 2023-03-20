//
// Created by 10259 on 2023/3/20.
//
#include <iostream>
#include <cmath>
#include "../Object/Robot.h"
#include "../Object/Workshop.h"
#include "../Object/Position.h"
using namespace std;


// 计算距离
double distance(Position p1, Position p2){
    return sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
}

// 机器人判断当前位置是否处于工作台附近
bool isNearWorkshop(Robot robot, Workshop workshop){
    Position robotPosition = robot.getPosition();
    Position workshopPosition = workshop.getPosition();
    double distanceToWorkshop = distance(robotPosition, workshopPosition);
    if(distanceToWorkshop <= 0.4){
        return true;
    } else{
        return false;
    }
}

// 机器人与工作台交互
