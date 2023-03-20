//
// Created by 10259 on 2023/3/20.
//

#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include "Deal.h"

bool Deal::initialization(Robot *robots, Workshop *workshops) {
    char line[1024];
    vector<int> vec;

    while(fgets(line, sizeof line, stdin)){
        if (line[0] == 'O' && line[1] == 'K') {
            return true;
        }

        int count = 0, i = 0;
        for(char s : line){
            count++;
            // 记录x，y；
            int x, y;
            x = count / 100;
            y = count % 100;
            auto m = double((x - 1) * 0.5 + 0.25);
            auto n = double((y - 1) * 0.5 + 0.25);

            if(s == '.'){  // 如果遇到.就跳过
                continue;
            }
            if(s == 'A'){  // 遇到机器人了
                Position position = Position(m, n);
                auto robot = Robot(position);
                robots[i] = robot;
                i++;
            }
            if(s >= '1' && s <= '9'){  // 遇到台子了
                int x = s - '0';
                Position position = Position(m, n);

                if(x == 4){
                    vec.push_back(1);
                    vec.push_back(2);
                    Workshop workshop = Workshop(x, position, vec);
                    workshops[x] = workshop;
                } else if(x == 5){
                    vec.push_back(1);
                    vec.push_back(3);
                    Workshop workshop = Workshop(x, position, vec);
                    workshops[x] = workshop;
                } else if(x == 6){
                    vec.push_back(2);
                    vec.push_back(3);
                    Workshop workshop = Workshop(x, position, vec);
                    workshops[x] = workshop;
                } else if(x ==7){
                    vec.push_back(4);
                    vec.push_back(5);
                    vec.push_back(6);
                    Workshop workshop = Workshop(x, position, vec);
                    workshops[x] = workshop;
                } else if(x == 8){
                    vec.push_back(7);
                    Workshop workshop = Workshop(x, position, vec);
                    workshops[x] = workshop;
                } else if(x == 9){
                    vec.push_back(1);
                    vec.push_back(2);
                    vec.push_back(3);
                    vec.push_back(4);
                    vec.push_back(5);
                    vec.push_back(6);
                    vec.push_back(7);
                    Workshop workshop = Workshop(x, position, vec);
                    workshops[x] = workshop;
                }

                vec.clear();
            }
        }
    }
    return false;

}

vector<int> Deal::calculateMaterialNum(int materialState) {
    int arr[100], i=0;

    while (materialState){
        arr[i] = materialState % 2;
        materialState /= 2;
        i++;
    }

    int count = 0;
    vector<int> materialNum;
    for(int j=i; j>=0; j--){
        if(arr[j] == 1){
            materialNum.push_back(count);
        } else{
            count ++;
        }
    }
    return materialNum;
}

bool Deal::readUntilOK(Robot *robots, Workshop *workshops, int &reward) {
    char line[1024];
    int robotNum = 0;
    int workshopNum;

    while (fgets(line, sizeof line, stdin)) {
        if (line[0] == 'O' && line[1] == 'K') {
            return true;
        }

        vector<double> vec;
        string str = line;  // 读取这一行
        char*p = strtok(line, " ");  // 以空格为分隔符，分割字符串
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
            int workType = vec[0];
            Position position = Position(vec[1], vec[2]);
            int leftProduceTime = int(vec[3]);
            int materialState = vec[4];
            vector<int> materialNum = calculateMaterialNum(materialState);
            int productState = int(vec[5]);

            workshops[workType].setWorkType(workType);
            workshops[workType].setPosition(position);
            workshops[workType].setLeftProduceTime(leftProduceTime);
            workshops[workType].setMaterialNum(materialNum);
            workshops[workType].setProductState(productState);
        } else if(vec.size() == 1){
            workshopNum = int(vec[0]);
            if (workshopNum != 9){
                return false;
            }
        } else if(vec.size() == 2){
            // 从这里可以读到frame
            reward = int(vec[1]);
        }
    }
    return false;
}

double Deal::distance(Position p1, Position p2) {
    return sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
}

bool Deal::isNearWorkshop(Robot robot, const Workshop &workshop) {
    Position robotPosition = robot.getPosition();
    Position workshopPosition = workshop.getPosition();
    double distanceToWorkshop = distance(robotPosition, workshopPosition);
    if(distanceToWorkshop <= 0.4){
        return true;
    } else{
        return false;
    }
}

vector<int> Deal::getMaterialNum(const Workshop &workshop) {
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

void Deal::interactWithWorkshop(Robot &robot, Workshop *workshops, int *flags) {
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
