#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <sstream>
#include "Object/Workshop.h"
#include "Object/Robot.h"
#include "Function/Init.cpp"
#include "Function/ReadFrame.cpp"
#include "Function/Action.cpp"
using namespace std;


Robot robots[4];
Workshop workshops[10];

int main() {
    initialization(robots, workshops);
    puts("OK");//标准输出“ok”并换行

    fflush(stdout);//冲洗流中的信息，缓冲区内的数据写回标准输出的文件中

    int frameID;//帧的id号
    int reward;//奖励
    while (scanf("%d", &frameID) != EOF) {//文件读入还没结束时进入循环
        readUntilOK(robots, workshops, reward);
        printf("%d\n", frameID);

        int flags[6] = {0, 0, 0, 0, 0, 0};

        for(int robotId = 0; robotId < 4; robotId++){
            interactWithWorkshop(robots[robotId], workshops, flags);
            LineSpeed lineSpeed = robots[robotId].getLineSpeed();
            printf("forward %d %f\n", robotId, lineSpeed.getModule());
            printf("rotate %d %f\n", robotId, robots[robotId].getRotate());

            if(flags[3] == 1){
                printf("sell %d\n", robotId);
                flags[3] = 0;
            }

            if(flags[4] == 1){
                printf("buy %d\n", robotId);
                flags[4] = 0;
            }
            // printf("destory %d\n", robotId); 暂时不涉及销毁物品
        }
        printf("OK\n", frameID);
        fflush(stdout);
    }
    return 0;
}
