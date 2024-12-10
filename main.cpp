#include <iostream>
#include <ctime>
#include "Object/Workshop.h"
#include "Object/Robot.h"
#include "Function/Deal.h"
using namespace std;


Robot robots[4];
Workshop workshops[51];

int main() {
    //  机器人是固定的，所以只需要初始化一次
    for(auto & robot : robots){
        robot = Robot();
    }

    int reward;  //奖励
    int workshopCount;  //工坊的数量
    Deal::readUntilOK(robots, workshops, reward, workshopCount);  //读取信息，直到读到OK为止
    puts("OK");//标准输出“ok”并换行
    fflush(stdout);//冲洗流中的信息，缓冲区内的数据写回标准输出的文件中

    vector<Workshop> robotFindworkshops;  // 对已经拿到东西的机器人而言的
    robotFindworkshops.reserve(51);  // 预留50个空间
    vector<Workshop> robotFindworkshops2;  // 对还没拿到东西的机器人而言的
    robotFindworkshops2.reserve(51);  // 预留50个空间

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

            Workshop w = Deal::findTargetWorkshop(robots[robotId], workshops, robotFindworkshops,robotFindworkshops2, workshopCount);
            Deal::action(robots[robotId], robots, w, lineSpeed, rotate);

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
            //if(){
            //    printf("destroy %d\n", robotId);
            //}
            // 统一重置vector
            robotFindworkshops.clear();
            robotFindworkshops2.clear();
        }
        printf("OK\n");
        fflush(stdout);
    }
    return 0;
}
