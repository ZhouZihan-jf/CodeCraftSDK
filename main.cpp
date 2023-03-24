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

    vector<Workshop> workshopVector;
    workshopVector.reserve(51);  // 预留51个空间

    int frameID = 0;//帧的id号
    double lineSpeed = 0.0;
    double rotate = 0.0;
    while (scanf("%d ", &frameID) != EOF) {//文件读入还没结束时进入循环
        Deal::readUntilOK(robots, workshops, reward, workshopCount);
        printf("%d\n", frameID);

        int flags[2] = {0, 0};  // 设置标记

        for(int robotId = 0; robotId < 4; robotId++){
            // 交互
            Deal::interactWithWorkshop(robots[robotId], workshops, workshopCount, flags);

            workshopVector = Deal::findWorkshops(robots[robotId], workshops, workshopCount);
            if(workshopVector.empty()){
                printf("forward %d %f\n", robotId, 2.5);
                printf("rotate %d %f\n", robotId, 1.5);
                if(flags[0] == 1){
                    printf("sell %d\n", robotId);
                    flags[0] = 0;
                }

                if(flags[1] == 1){
                    printf("buy %d\n", robotId);
                    flags[1] = 0;
                }
                continue;  // 如果没有找到工坊，就不用执行下面的代码了
            }

            Deal::action(robots[robotId], workshopVector[0], lineSpeed, rotate);

            printf("forward %d %f\n", robotId, lineSpeed);  // lineSpeed.getModule()
            printf("rotate %d %f\n", robotId, rotate);  // robots[robotId].getRotate()

            if(flags[0] == 1){
                printf("sell %d\n", robotId);
                flags[0] = 0;
            }

            if(flags[1] == 1){
                printf("buy %d\n", robotId);
                flags[1] = 0;
            }
            // printf("destory %d\n", robotId); 暂时不涉及销毁物品
        }
        printf("OK\n");
        fflush(stdout);
    }
    return 0;
}
