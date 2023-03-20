//
// Created by 10259 on 2023/3/20.
//
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "../Object/Robot.h"
#include "../Object/Workshop.h"
#include "../Object/Position.h"


// 计算距离
double distance(Position p1, Position p2){
    return sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
}

// 机器人判断当前位置是否处于工作台附近
bool isNearWorkshop(Robot robot, const Workshop& workshop){
    Position robotPosition = robot.getPosition();
    Position workshopPosition = workshop.getPosition();
    double distanceToWorkshop = distance(robotPosition, workshopPosition);
    if(distanceToWorkshop <= 0.4){
        return true;
    } else{
        return false;
    }
}

// 判断当前工作台缺哪些原材料
vector<int> getMaterialNum(const Workshop& workshop){
    vector<int> materialNum = workshop.getMaterialNum();
    vector<int> needMaterialNum = workshop.getNeedMaterialNum();
    vector<int> num;
    for(int & i : materialNum){
        if(find(needMaterialNum.begin(), needMaterialNum.end(), i) != needMaterialNum.end()){
            needMaterialNum.erase(find(needMaterialNum.begin(), needMaterialNum.end(), i));
        }
    }

    return needMaterialNum;
}
// 判断机器人是否拥有台子所需的原材料

// 机器人与工作台交互
void interactWithWorkshop(Robot &robot, Workshop workshops[], int flags[]){
    int workshopId = robot.getWorkshopId();
    Workshop workshop = workshops[workshopId]; // 找到对应的工作台

    //不处于工作台附近就退出
    if(workshopId == -1 || !isNearWorkshop(robot, workshop)){
        return;
    }

    vector<int> materialNum = workshop.getMaterialNum();  // 获取工作台上的原材料类型
    vector<int> needMaterialNum = getMaterialNum(workshop);  // 获取工作台还缺的原材料类型

    // 机器人携带物品类型不为0，即携带有原材料，同时工作台还缺对应的原材料，那么要找台子放原材料，即卖出
    if(find(needMaterialNum.begin(), needMaterialNum.end(), robot.getItemType()) != needMaterialNum.end() && robot.getItemType() != 0){
        materialNum.push_back(robot.getItemType());  // 工作台上的原材料类型为机器人携带的原材料类型
        workshop.setMaterialNum(materialNum);
        robot.setItemType(0);  // 机器人会卖出携带物品类型为0，即空手
        flags[3] = 1;  // sell
    }

    // 机器人携带物品类型为0，即空手，同时工作台也生产好了，那么要找台子拿产品，即买入
    if(robot.getItemType() == 0 && workshop.getProductState() == 1){
        robot.setItemType(workshopId);  // 机器人携带物品类型为工作台上的产品类型
        workshop.setProductState(0);  // 设置工作台上的产品状态为0，即无产品
        flags[4] = 1;  // buy
    }

}