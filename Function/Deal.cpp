//
// Created by 10259 on 2023/3/20.
//
#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
#include "Deal.h"

// 根据materialState的值，将其转化为二进制，然后将二进制中的1的位置记录下来，即为materialNum的值
// 例如：materialState = 5，即101，那么materialNum = {0, 2}
vector<int> Deal::calculateMaterialNum(int materialState) {
    int arr[100], i=0;

    while (materialState){
        arr[i] = materialState % 2;
        materialState /= 2;
        i++;
    }

    int count = 0;
    vector<int> materialNum;
    materialNum.reserve(8);  // 预留5个空间
    for(int j=0; j<i; j++){
        if(arr[j] == 1){
            materialNum.push_back(count);
            count ++;
        } else{
            count ++;
        }
    }
    return materialNum;
}

// 读取信息，直到读到OK为止
bool Deal::readUntilOK(Robot *robots, Workshop *workshops, int &reward, int &workshopCount) {
    char line[1024];
    int robotNum = 0;
    int workshopNum = 0;
    int workshopId = 0;
    vector<double> vec;
    vector<int> materialNum;
    vec.reserve(11);  // 预留11个空间
    materialNum.reserve(8);  // 预留5个空间

    while (fgets(line, sizeof line, stdin)) {
        if (line[0] == 'O' && line[1] == 'K') {
            workshopCount = workshopNum;
            return true;
        }

        char* p = strtok(line, " ");  // 以空格为分隔符，分割字符串
        while(p != nullptr){
            vec.push_back(atof(p));  // 将分割后的字符串转化为double类型
            p = strtok(nullptr, " ");
        }

        // 根据读取的信息，将其存入相应的对象中
        if(vec.size() == 10){  // 说明是机器人的信息
            if(robotNum > 3){
                return false;
            }
            int workshopID = int(vec[0]);
            int itemType = int(vec[1]);
            double timeWorth = vec[2];
            double collisionWorth = vec[3];
            double rotate = vec[4];
            LineSpeed lineSpeed = LineSpeed(vec[5], vec[6]);
            double toward = vec[7];
            Position position = Position(vec[8], vec[9]);

            robots[robotNum].setWorkshopId(workshopID);
            robots[robotNum].setItemType(itemType);
            robots[robotNum].setTimeWorth(timeWorth);
            robots[robotNum].setCollisionWorth(collisionWorth);
            robots[robotNum].setRotate(rotate);
            robots[robotNum].setLineSpeed(lineSpeed);
            robots[robotNum].setToward(toward);
            robots[robotNum].setPosition(position);
            robotNum ++;
        } else if(vec.size() == 6){  // 说明是工作台的信息
            workshopId ++;
            if(workshopId > workshopNum){
                return false;
            }

            int workType = vec[0];
            Position position = Position(vec[1], vec[2]);
            int leftProduceTime = int(vec[3]);
            int materialState = vec[4];
            materialNum.clear();
            materialNum = calculateMaterialNum(materialState);
            int productState = int(vec[5]);

            Workshop workshop = Workshop();
            workshop.setNumber(workshopId);
            workshop.setWorkType(workType);
            workshop.setPosition(position);
            workshop.setLeftProduceTime(leftProduceTime);
            workshop.setMaterialNum(materialNum);
            workshop.setNeedMaterialNum(workType);
            workshop.setProductState(productState);

            workshops[workshopId] = workshop;  // 将工作台信息存入数组中
        } else if(vec.size() == 1){
            // 读取工作台总数
            workshopNum = int(vec[0]);
        } else if(vec.size() == 2){
            // 从这里可以读到frame
            reward = int(vec[1]);
        }
        vec.clear();
    }

    return false;
}

// 计算距离
double Deal::distance(Position p1, Position p2) {
    return sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
}

// 机器人判断当前位置是否处于工作台附近
int Deal::isNearWorkshop(Robot robot, Workshop* workshops, int workshopCount) {
    //int workshopId = robot.getWorkshopId();
    //if(workshopId != -1){
    //    return workshopId;
    //}
    Position robotPosition = robot.getPosition();
    Position workshopPosition;
    for(int i =1 ; i<=workshopCount; i++){
        workshopPosition = workshops[i].getPosition();
        double distanceToWorkshop = distance(robotPosition, workshopPosition);
        if(distanceToWorkshop <= 0.4){
            return i;
        }
    }

    return -1;
}

// 判断当前工作台缺哪些原材料
vector<int> Deal::getMaterialNum(const Workshop &workshop) {
    vector<int> materialNum = workshop.getMaterialNum();
    vector<int> needMaterialNum = workshop.getNeedMaterialNum();

    for(int & i : materialNum){
        if(find(needMaterialNum.begin(), needMaterialNum.end(), i) != needMaterialNum.end()){
            needMaterialNum.erase(find(needMaterialNum.begin(), needMaterialNum.end(), i));
        }
    }

    return needMaterialNum;
}

// 机器人与工作台交互
void Deal::interactWithWorkshop(Robot &robot, Workshop *workshops, int workshopCount, int *flags) {
    int workshopId;
    Workshop workshop;

    workshopId = isNearWorkshop(robot, workshops, workshopCount);

    if (workshopId == -1 || workshopId > workshopCount){
        return;
    }else{
        workshop = workshops[workshopId];
    }

    vector<int> materialNum;
    materialNum.reserve(8);  // 预留5个空间
    materialNum = workshop.getMaterialNum();  // 获取工作台上的原材料类型
    vector<int> needMaterialNum;
    needMaterialNum.reserve(8);  // 预留10个空间
    needMaterialNum = getMaterialNum(workshop);  // 获取工作台缺少的原材料类型

    // 机器人携带物品类型不为0，即携带有原材料，同时工作台还缺对应的原材料，那么要找台子放原材料，即卖出
    if(find(needMaterialNum.begin(), needMaterialNum.end(), robot.getItemType()) != needMaterialNum.end() && robot.getItemType() != 0){
        materialNum.push_back(robot.getItemType());  // 工作台上的原材料类型为机器人携带的原材料类型
        workshop.setMaterialNum(materialNum);
        robot.setItemType(0);  // 机器人会卖出携带物品,此时类型为0，即空手
        flags[0] = 1;  // sell
    }

    // 机器人携带物品类型为0，即空手，同时工作台也生产好了，那么要找台子拿产品，即买入
    if(robot.getItemType() == 0 && workshop.getProductState() == 1){
        robot.setItemType(workshop.getWorkType());  // 机器人携带物品类型为工作台上的产品类型
        workshop.setProductState(0);  // 设置工作台上的产品状态为0，即无产品
        flags[1] = 1;  // buy
    }

    workshops[workshopId] = workshop;  // 保留对工作台的修改
}

int Deal:: isRightDirection(Robot &robot, const Workshop& workshop) {
    Position robotPosition = robot.getPosition();
    Position workshopPosition = workshop.getPosition();
    Position fuzhuPosition = Position(robotPosition.getX()+1, robotPosition.getY());

    double PI = 3.14159265359;
    double toward = robot.getToward();  // 得到robot的朝向
    // 计算目标向量与x轴正方向的夹角
    double distA = distance(robotPosition, workshopPosition);
    double x1 = workshopPosition.getX() - robotPosition.getX();
    double y1 = workshopPosition.getY() - robotPosition.getY();

    double cos = x1 / distA;
    double angle = acos(cos);  // 以robot为原点建立坐标系，返回目的地工作台与水平线的夹角


    if(y1 < 0){
        angle = - angle;
    }


    double tag = toward - angle;  // 机器人朝向与目的地工作台与水平线的夹角的差值


    if(tag > 0.023 && tag < PI - 0.023){
        return 1;  // 顺时针转
    }else if(tag > PI + 0.023 && tag < 2*PI - 0.023) {
        return -1;  // 逆时针转
    }else if(tag > -PI + 0.023 && tag < 0 - 0.023) {
        return -1;  // 逆时针转
    }else if(tag > -2*PI + 0.023 && tag < -PI - 0.023) {
        return 1;  // 顺时针转
    }

    return 0;  // 朝向正确
}

void Deal::action(Robot &robot, const Robot robots[], const Workshop &workshop, double& lineSpeed, double& rotateSpeed){
    double PI = 3.14159265359;
    Position robotPosition = robot.getPosition();  // 获得机器人的位置
    int rightDirection = isRightDirection(robot, workshop);  // 判断机器人朝向是否正确

    if(distance(robotPosition, workshop.getPosition()) <= 0.4) {  // 机器人已经到达交互范围中
        // 机器人到达交互范围中，但是工作台在边界
        if(workshop.getPosition().getX() < 0.3 || workshop.getPosition().getX() > 49.7
        || workshop.getPosition().getY() < 0.3 || workshop.getPosition().getY() > 49.7){
            robot.setRotate(3.0);
            rotateSpeed = 3.0;
        }else{
            robot.setRotate(0.0);
            rotateSpeed = 0.0;
        }
        lineSpeed = 0.0;
    }else{
        if(rightDirection == 1){  // 顺时针转
            // 修改角速度
            robot.setRotate(-3.0);
            rotateSpeed = -3.0;
            // 修改线速度
            lineSpeed = 3.5;
        }else if(rightDirection == -1){  // 逆时针转
            // 修改角速度
            robot.setRotate(3.0);
            rotateSpeed = 3.0;
            // 修改线速度
            lineSpeed = 3.5;
        }else{  // 朝向正确
            // 修改角速度
            robot.setRotate(0.0);
            rotateSpeed = 0.0;
            // 修改线速度
            lineSpeed = 6.0;
        }
    }

    // 解决机器人之间碰撞问题
    for(int i = 0; i < 4; i++){
        // 跳过当前机器人
        if(robot.getPosition().getX() == robots[i].getPosition().getX()
        && robot.getPosition().getY() == robots[i].getPosition().getY()){
            continue;
        }
        // 相向碰撞
        if((abs(robot.getToward() - robots[i].getToward()) >= 0.8*PI && abs(robot.getToward() - robots[i].getToward()) <= PI)
        && distance(robot.getPosition(), robots[i].getPosition()) <= 1.0){
            robot.setRotate(2.0);
            rotateSpeed = 2.0;
            lineSpeed = 1.0;
        }
        /*
        // 同向碰撞
        if((abs(robot.getToward() - robots[i].getToward()) >= 0 && abs(robot.getToward() - robots[i].getToward()) <= 0.2*PI)
           && distance(robot.getPosition(), robots[i].getPosition()) <= 1.0){
            // 修改角速度
            robot.setRotate(.0);
            rotateSpeed = 0.0;
            // 修改线速度
            lineSpeed = 2.0;
        }
         */
    }
}

// 机器人发现一定范围内的工作台，返回工作台向量，方便后续寻路
vector<Workshop> Deal::findWorkshops(Robot robot, Workshop *workshops, int workshopCount) {
    vector<Workshop> robotFindworkshops;
    robotFindworkshops.reserve(50);  // 预留50个空间

    int good = robot.getItemType();  // 获取机器人携带物品类型
    int workshopId = robot.getWorkshopId();  // 获取机器人当前所在工作台id
    vector<int> needMaterialNum;  // 获取工作台还缺的原材料类型
    needMaterialNum.reserve(8);  // 预留8个空间

    for (int i = 1; i <= workshopCount; i++) {
        if (i == workshopId) {  // 跳过现在正在交互的工作台
            continue;
        }
        needMaterialNum = getMaterialNum(workshops[i]);  // 获取工作台还缺的原材料类型
        // 如果工作台上缺的东西和机器人携带物品类型(真带东西了)一致，那么就加入vector
        if (good != 0 && find(needMaterialNum.begin(), needMaterialNum.end(), good) != needMaterialNum.end()) {
            robotFindworkshops.push_back(workshops[i]);
        }
        // 如果机器人没带东西，那么就加入所有生产了东西的工作台
        if (good == 0 && workshops[i].getProductState() == 1){
            robotFindworkshops.push_back(workshops[i]);
        }
    }

    // 对robotFindworkshops进行排序，按照距离从近到远
    sort(robotFindworkshops.begin(), robotFindworkshops.end(), [&](Workshop a, Workshop b){
        return distance(robot.getPosition(), a.getPosition()) < distance(robot.getPosition(), b.getPosition());
    });

    return robotFindworkshops;
}

vector<Workshop> Deal::initFindWorkshops(Robot robot, Workshop *workshops, int workshopCount) {
    vector<Workshop> robotFindworkshops;
    robotFindworkshops.reserve(50);  // 预留50个空间

    int good = robot.getItemType();  // 获取机器人携带物品类型
    int workshopId = robot.getWorkshopId();  // 获取机器人当前所在工作台id
    vector<int> needMaterialNum;  // 获取工作台还缺的原材料类型
    needMaterialNum.reserve(8);  // 预留8个空间

    for (int i = 1; i <= workshopCount; i++) {
        if (i == workshopId) {  // 跳过现在正在交互的工作台
            continue;
        }
        if (workshops[i].getWorkType() > 4) {
            continue;
        }
        needMaterialNum = getMaterialNum(workshops[i]);  // 获取工作台还缺的原材料类型
        // 如果工作台上缺的东西和机器人携带物品类型(真带东西了)一致，那么就加入vector
        if (good != 0 && find(needMaterialNum.begin(), needMaterialNum.end(), good) != needMaterialNum.end()) {
            robotFindworkshops.push_back(workshops[i]);
        }
        // 如果机器人没带东西，那么就加入所有生产了东西的工作台
        if (good == 0 && workshops[i].getProductState() == 1){
            robotFindworkshops.push_back(workshops[i]);
        }
    }

    // 对robotFindworkshops进行排序，按照距离从近到远
    sort(robotFindworkshops.begin(), robotFindworkshops.end(), [&](Workshop a, Workshop b){
        return distance(robot.getPosition(), a.getPosition()) < distance(robot.getPosition(), b.getPosition());
    });

    return robotFindworkshops;
}

double G(const Workshop& workshop, const Robot& robot){
    double reward = 0.0;
    if(workshop.getWorkType() == 1){
        reward = 3000.0;
    } else if(workshop.getWorkType() == 2){
        reward = 3200.0;
    } else if(workshop.getWorkType() == 3){
        reward = 3400.0;
    } else if(workshop.getWorkType() == 4){
        reward = 7100.0;
    } else if(workshop.getWorkType() == 5){
        reward = 7800.0;
    } else if(workshop.getWorkType() == 6){
        reward = 8300.0;
    } else if(workshop.getWorkType() == 7){
        reward = 29000.0;
    }
    double d = Deal::distance(robot.getPosition(), workshop.getPosition());

    return reward / d;
}

Workshop Deal::findTargetWorkshop(Robot robot, Workshop *workshops, int workshopCount) {
    Workshop targetWorkshop;

    int good = robot.getItemType();  // 获取机器人携带物品类型
    int workshopId = robot.getWorkshopId();  // 获取机器人当前所在工作台id
    vector<int> needMaterialNum1;  // 获取工作台还缺的原材料类型
    needMaterialNum1.reserve(8);  // 预留8个空间
    vector<int> needMaterialNum2;  // 获取工作台还缺的原材料类型
    needMaterialNum2.reserve(8);  // 预留8个空间
    vector<Workshop> robotFindworkshops;
    robotFindworkshops.reserve(50);  // 预留50个空间

    for (int i = 1; i <= workshopCount; i++) {
        if (i == workshopId) {  // 跳过现在正在交互的工作台
            continue;
        }
        needMaterialNum1 = getMaterialNum(workshops[i]);  // 获取工作台还缺的原材料类型
        // 如果工作台上缺的东西和机器人携带物品类型(真带东西了)一致，那么就加入vector
        if (good != 0 && find(needMaterialNum1.begin(), needMaterialNum1.end(), good) != needMaterialNum1.end()) {
            robotFindworkshops.push_back(workshops[i]);
        }
        // 如果机器人没带东西，那么就加入所有生产了东西的工作台
        if (good == 0 && workshops[i].getProductState() == 1){
            if(G(workshops[i], robot) < 0){  // 判断是否有利可图
                continue;
            }
            int product = workshops[i].getWorkType();  // 获取工作台生产的东西
            // 已经生产的product能不能卖掉
            for(int j = 1; j <= workshopCount; j++) {  // 找到能卖的序列
                if(j == workshopId){  // 跳过现在正在交互的工作台
                    continue;
                }
                needMaterialNum2 = getMaterialNum(workshops[j]);  // 获取工作台还缺的原材料类型
                if (find(needMaterialNum2.begin(), needMaterialNum2.end(), product) != needMaterialNum2.end()) {
                        targetWorkshop = workshops[i];
                        break;
                }
            }
        }
    }

    if(good != 0){  // 如果机器人带东西，那么就找最近的工作台
        // 对robotFindworkshops进行排序，按照距离从近到远
        sort(robotFindworkshops.begin(), robotFindworkshops.end(), [&](Workshop a, Workshop b){
            return distance(robot.getPosition(), a.getPosition()) < distance(robot.getPosition(), b.getPosition());
        });
        targetWorkshop = robotFindworkshops[0];
    }

    return targetWorkshop;
}




