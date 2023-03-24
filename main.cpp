#include <iostream>
#include "Object/Workshop.h"
#include "Object/Robot.h"
#include "Object/LineSpeed.h"
#include "Function/Deal.h"
using namespace std;


Robot robots[4];
Workshop workshops[51];

int main() {
    //  机器人是固定的，所以只需要初始化一次
    for(int i = 0; i < 4; i++){
        robots[i] = Robot();
    }

    int reward;  //奖励
    int workshopCount;  //工坊的数量
    Deal::readUntilOK(robots, workshops, reward, workshopCount);  //读取信息，直到读到OK为止
    puts("OK");//标准输出“ok”并换行
    fflush(stdout);//冲洗流中的信息，缓冲区内的数据写回标准输出的文件中

    int frameID = 0;//帧的id号
    while (scanf("%d ", &frameID) != EOF) {//文件读入还没结束时进入循环
        Deal::readUntilOK(robots, workshops, reward, workshopCount);
        printf("%d\n", frameID);

        int flags[6] = {0, 0, 0, 0, 0, 0};  // 设置标记

        for(int robotId = 0; robotId < 4; robotId++){
            Deal::interactWithWorkshop(robots[robotId], workshops, workshopCount, flags);
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
        printf("OK\n");
        fflush(stdout);
    }
    return 0;
}
