
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
    for(int j=i; j>=0; j--){
        if(arr[j] == 1){
            materialNum.push_back(count);
        } else{
            count ++;
        }
    }
    return materialNum;
}

//时间价值系数和碰撞价值系数的计算函数
double compute_f(double x,double maxX,double minRate)
{
    if(x >= maxX)
        return minRate;
    else
    {
        double res = (1-(sqrt(1- pow(1-(x/maxX),2)))) * (1-minRate) + minRate;
        return res;
    }
}
//碰撞冲量计算函数 I 是冲量(有时也记作J)； F 是作用的力； dt 是一段无限小的时间。 其他的定义方法有： 、 、 等。
//冲量等于物体动量的变化量。
double compute_collsion_impulse(Robot robot1,Robot robot2)
{
    double p1,p2;
    double q1,q2;
    double m1,m2;
    if(robot1.getItemType() == 0)
    {
        m1 = 20 * M_PI * 0.45 * 0.45;
        p1 = robot1.getLineSpeed().getModule() * m1;
    }
    else if(robot1.getItemType() >= 1 && robot1.getItemType() <= 7)
    {
        m1 = 20 * M_PI * 0.53 * 0.53;
        p1 = robot1.getLineSpeed().getModule() * m1;
    }
    if(robot2.getItemType() == 0)
    {
        m2 = 20 * M_PI * 0.45 * 0.45;
        p2 = robot2.getLineSpeed().getModule() * m2;
    }
    else if(robot2.getItemType() >= 1 && robot2.getItemType() <= 7)
    {
        m2 = 20 * M_PI * 0.53 * 0.53;
        p2 = robot2.getLineSpeed().getModule() * m2;
    }
    q1 = m1 + m1 * pow((robot1.getLineSpeed().getModule()- 0.5),2);
    q2 = m2 + m2 * pow((robot2.getLineSpeed().getModule() - 0.5),2);
    robot1.setCollisionWorth(q1 - p1);
    robot2.setCollisionWorth(q2 - p2);
    return 1;
}
//物品售价计算公式
double compute_sell_price(int primary_price,int frameid,double collsion_impulse)
{
    double timeWorth = compute_f(frameid,9000,0.8);
    double collisionWorth = compute_f(collsion_impulse,1000,0.8);
    double sell_price = primary_price * timeWorth * collisionWorth;
    return sell_price;
}

// 读取信息，直到读到OK为止
bool Deal::readUntilOK(Robot *robots, Workshop *workshops, double &reward, int &workshopCount) {
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
            vec.~vector();
            materialNum.~vector();
            return true;
        }

        char* p = strtok(line, " ");  // 以空格为分隔符，分割字符串
        while(p != nullptr){
            vec.push_back(atof(p));  // 将分割后的字符串转化为double类型
            p = strtok(nullptr, " ");
        }

        // 根据读取的信息，将其存入相应的对象中
        if(vec.size() == 10){  // 说明是机器人的信息
            if(robotNum >= 3){
                return false;
            }
            int workshopId = int(vec[0]);
            int itemType = int(vec[1]);
            double timeWorth = vec[2];
            double collisionWorth = vec[3];
            double rotate = vec[4];
            LineSpeed lineSpeed = LineSpeed(vec[5], vec[6]);
            double toward = vec[7];
            Position position = Position(vec[8], vec[9]);

            robots[robotNum].setWorkshopId(workshopId);
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
            workshop.setWorkType(workType);
            workshop.setPosition(position);
            workshop.setLeftProduceTime(leftProduceTime);
            workshop.setMaterialNum(materialNum);
            workshop.setNeedMaterialNum(workType);
            workshop.setProductState(productState);

            workshops[workshopId] = workshop;  // 将工作台信息存入数组中

            workshop.~Workshop();
        } else if(vec.size() == 1){
            // 读取工作台总数
            workshopNum = int(vec[0]);
        } else if(vec.size() == 2){
            // 从这里可以读到frame
            reward = int(vec[1]);
        }
        vec.clear();
    }

    vec.~vector();  // 释放内存
    materialNum.~vector();  // 释放内存
    return false;
}

// 计算距离
double Deal::distance(Position p1, Position p2) {
    return sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
}

// 机器人判断当前位置是否处于工作台附近
bool Deal::isNearWorkshop(Robot robot, Workshop* workshops, int count) {
    Position robotPosition = robot.getPosition();
    Position workshopPosition = workshops[count].getPosition();
    double distanceToWorkshop = distance(robotPosition, workshopPosition);
    if(distanceToWorkshop <= 0.4){
        return true;
    } else{
        return false;
    }
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

    materialNum.~vector();

    return needMaterialNum;
}

// 机器人与工作台交互
void Deal::interactWithWorkshop(Robot &robot, Workshop *workshops, material *material,int workshopCount, int *flags,int framesid,double &reward) {
    int workshopId = robot.getWorkshopId();
    Workshop workshop = Workshop();
    int itemtype = robot.getItemType();
    for(int i = 1; i <= workshopCount; i++){
        //不处于工作台附近就退出
        if(workshopId == -1 || !isNearWorkshop(robot, workshops, i)){
            return;
        }
        // 找到对应的工作台
        if(workshops[i].set_type_workshop(workshops->getWorkType(),itemtype) == 1 && isNearWorkshop(robot, workshops, i)){  // 类型一致同时还正好是离得近的那一个台子
            workshop = workshops[i];
            break;
        }
    }

    vector<int> materialNum = workshop.getMaterialNum();  // 获取工作台上的原材料类型
    materialNum.reserve(8);  // 预留5个空间
    vector<int> needMaterialNum = getMaterialNum(workshop);  // 获取工作台还缺的原材料类型
    needMaterialNum.reserve(8);  // 预留10个空间

    // 机器人携带物品类型不为0，即携带有原材料，同时工作台还缺对应的原材料，那么要找台子放原材料，即卖出
    if(find(needMaterialNum.begin(), needMaterialNum.end(), robot.getItemType()) != needMaterialNum.end() && robot.getItemType() != 0){
        materialNum.push_back(robot.getItemType());  // 工作台上的原材料类型为机器人携带的原材料类型
        workshop.setMaterialNum(materialNum);
        robot.setItemType(0);  // 机器人会卖出携带物品类型为0，即空手
        flags[3] = 1;  // sell
        reward = compute_sell_price(material[robot.getItemType()].get_primary_sell_price(),framesid,robot.getCollisionWorth()) - material[robot.getItemType()].get_buy_price();
    }

    // 机器人携带物品类型为0，即空手，同时工作台也生产好了，那么要找台子拿产品，即买入
    if(robot.getItemType() == 0 && workshop.getProductState() == 1){
        robot.setItemType(workshopId);  // 机器人携带物品类型为工作台上的产品类型
        workshop.setProductState(0);  // 设置工作台上的产品状态为0，即无产品
        flags[4] = 1;  // buy
        reward = reward - material[workshopId].get_buy_price();//买完东西之后，reward值发生变化
    }

    materialNum.~vector();
    needMaterialNum.~vector();
    workshop.~Workshop();
}

