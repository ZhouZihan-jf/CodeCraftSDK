#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <sstream>
#include "Object/Workshop.h"
#include "Object/Robot.h"
#include "Function/Init.cpp"
#include "Function/ReadFrame.cpp"
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
        int lineSpeed = 3;
        double angleSpeed = 1.5;
        for(int robotId = 0; robotId < 4; robotId++){
            printf("forward %d %d\n", robotId, lineSpeed);
            printf("rotate %d %f\n", robotId, angleSpeed);
            printf("buy %d\n", robotId);
            printf("sell %d\n", robotId);
            printf("destory %d\n", robotId);
        }
        printf("OK\n", frameID);
        fflush(stdout);
    }
    return 0;
}
