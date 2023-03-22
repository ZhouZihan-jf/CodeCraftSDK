#include <iostream>
#include "Object/Workshop.h"
#include "Object/Robot.h"
#include "Object/LineSpeed.h"
#include "Object/material.h"
#include "Function/Deal.h"
using namespace std;


Robot robots[4];
Workshop workshops[51];
material material[8];
void set_material()
{
    material[1].set_type(1);
    material[1].set_formulation();
    material[1].set_buy_price(3000);
    material[1].set_primary_sell_price(6000);
    material[2].set_type(2);
    material[2].set_formulation();
    material[2].set_buy_price(4400);
    material[2].set_primary_sell_price(7600);
    material[3].set_type(3);
    material[3].set_formulation();
    material[3].set_buy_price(5800);
    material[3].set_primary_sell_price(9200);
    material[4].set_type(4);
    material[4].set_formulation();
    material[4].set_buy_price(15400);
    material[4].set_primary_sell_price(22500);
    material[5].set_type(5);
    material[5].set_formulation();
    material[5].set_buy_price(17200);
    material[5].set_primary_sell_price(25000);
    material[6].set_type(6);
    material[6].set_formulation();
    material[6].set_buy_price(19200);
    material[6].set_primary_sell_price(27500);
    material[7].set_type(7);
    material[7].set_formulation();
    material[7].set_buy_price(76000);
    material[7].set_primary_sell_price(105000);
}
int main() {
    //  机器人是固定的，所以只需要初始化一次
    for(int i = 0; i < 4; i++){
        robots[i] = Robot();
    }
    //物品类型是固定的，所以只需要初始化一次
    set_material();

    double reward;  //奖励
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
            Deal::interactWithWorkshop(robots[robotId], workshops,material, workshopCount, flags,frameID,reward);
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
