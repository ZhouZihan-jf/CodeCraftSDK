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
    vec.reserve(12);  // 预留11个空间
    vector<int> materialNum;
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
    materialNum.reserve(10);
    vector<int> needMaterialNum = workshop.getNeedMaterialNum();
    needMaterialNum.reserve(10);

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
    double yu = 0.035;  // 设定一定的阈值

    if(tag > yu && tag < PI - yu){
        return 1;  // 顺时针转
    }else if(tag > PI + yu && tag < 2*PI - yu) {
        return -1;  // 逆时针转
    }else if(tag > -PI + yu && tag < 0 - yu) {
        return -1;  // 逆时针转
    }else if(tag > -2*PI + yu && tag < -PI - yu) {
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
    }else if(distance(robotPosition, workshop.getPosition()) > 0.4
    && distance(robotPosition, workshop.getPosition()) < 0.8
    && rightDirection != 0){
        if(rightDirection == 1){  // 顺时针转
            // 修改角速度
            robot.setRotate(-3.14);
            rotateSpeed = -3.14;
            // 修改线速度
            lineSpeed = 2.0;
        }else{  // 逆时针转
            // 修改角速度
            robot.setRotate(3.14);
            rotateSpeed = 3.14;
            // 修改线速度
            lineSpeed = 2.0;
        }
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
    }
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
        reward = 7100.0 * 2.0;
    } else if(workshop.getWorkType() == 5){
        reward = 7800.0 * 2.5;
    } else if(workshop.getWorkType() == 6){
        reward = 8300.0 * 3.0;
    } else if(workshop.getWorkType() == 7){
        reward = 29000.0 * 5;
    }
    double d = Deal::distance(robot.getPosition(), workshop.getPosition());

    return reward / d;
}

bool isCanRecive(const Workshop& workshop, int good){
    vector<int> needMaterialNum = Deal::getMaterialNum(workshop);
    if(find(needMaterialNum.begin(), needMaterialNum.end(), good) != needMaterialNum.end()){
        return true;
    }
    return false;
}

Workshop Deal::findTargetWorkshop(Robot robot, Workshop *workshops, vector<Workshop>& w1, vector<Workshop>& w2,  int workshopCount) {
    Workshop targetWorkshop;

    int good = robot.getItemType();  // 获取机器人携带物品类型
    int workshopId = robot.getWorkshopId();  // 获取机器人当前所在工作台id
    vector<int> needMaterialNum;  // 获取工作台还缺的原材料类型
    needMaterialNum.reserve(10);  // 预留8个空间


    if(good != 0){
        for(int i = 1; i<= workshopCount; i++){
            if(i == workshopId){  // 跳过现在正在交互的工作台
                continue;
            }
            needMaterialNum = getMaterialNum(workshops[i]);  // 获取工作台还缺的原材料类型
            // 如果工作台上缺的东西和机器人携带物品类型(真带东西了)一致，那么就加入vector
            if(find(needMaterialNum.begin(), needMaterialNum.end(), good) != needMaterialNum.end()){
                w1.push_back(workshops[i]);
            }
            needMaterialNum.clear();
        }

        // 对robotFindworkshops进行排序，按照距离从近到远
        sort(w1.begin(), w1.end(), [&](Workshop a, Workshop b){
            return distance(robot.getPosition(), a.getPosition()) < distance(robot.getPosition(), b.getPosition());
        });
        targetWorkshop = w1[0];
    }else{
        // 得到候补序列
        for(int i = 1; i <= workshopCount; i++){
            if(i == workshopId){  // 跳过现在正在交互的工作台
                continue;
            }
            for(int j = 1; j<= workshopCount; j++){
                if(j == i){  // 跳过自己
                    continue;
                }
                if(workshops[i].getProductState() == 1 && isCanRecive(workshops[j], workshops[i].getWorkType())){
                    w2.push_back(workshops[i]);  // 可以买到也能卖出去
                }
            }
        }
        // 对robotFindworkshops进行排序，按照从值还是不值
        sort(w2.begin(), w2.end(), [&](Workshop a, Workshop b){
            return G(a, robot) > G(b, robot);
        });
        targetWorkshop = w2[0];
    }

    return targetWorkshop;
}




