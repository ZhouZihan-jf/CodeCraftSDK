//
// Created by 10259 on 2023/3/19.
//
#include <iostream>
#include<cstdlib>
#include<vector>
#include <cstring>
#include "../Object/Robot.h"
#include "../Object/Workshop.h"


// 根据materialState的值，将其转化为二进制，然后将二进制中的1的位置记录下来，即为materialNum的值
// 例如：materialState = 5，即101，那么materialNum = {0, 2}
vector<int> calculateMaterialNum(int materialState){
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

bool readUntilOK(Robot robots[], Workshop workshops[], int &reward){
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



