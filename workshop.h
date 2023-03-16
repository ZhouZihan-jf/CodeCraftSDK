#include <iostream>
#include <cmath>
#ifndef CODECRAFTSDK_WORKSHOP_H
#define CODECRAFTSDK_WORKSHOP_H

class workshop {
private:
    int worktype;//工作台类型，工作台type,定义完成后不改变
    float x,y;//所处的位置x，y坐标
    int left_produce_time;//用帧数表示剩余生产时间
    int material_state;//原材料状态，用二进制表转换得到，有7种原材料，需要七位
    int product_state;//产品格状态，只有0和1，表示有无
    int number;//工作台自身编号,从0开始
public:
    workshop();//默认构造函数
    bool set_workid(int id)//设置工作台的id号
    {
        worktype = id;
        if(worktype < 1 || worktype > 9)
            return true;
        else
            return false;
    }
    int set_locationx(float x1)//设置坐标位置
    {
        x = x1;
        return 1;
    }
    int set_locationy(float y1)//设置坐标位置
    {
        y = y1;
        return 1;
    }
    int set_left_time(int time)//设置剩余生产时间，以帧数为计量单位
    {
        left_produce_time = time;
        if (left_produce_time == -1)
        {
            //print("there is no product!")
            return -1;
        }
        else if (left_produce_time == 0)
        {
            //print("the grid is full and blocked because of the produce!")
            return 0;
        }
        else if (left_produce_time > 0)
            //print("there is %d frames left!")
            return left_produce_time;
        else
            return -2;
    }
    int set_material_state(int num)
    {
        material_state = num;
        int a[8] = {0};//用于表示有哪几种原材料，为1则有该种原材料，为0则没有该种原材料
        int tem;
        int i = 7,j = 5;//i表示数组的下标，j表示二进制位表的最高级数
        while(num > 0)
        {
            tem = num / pow(2,j);
            num = num - pow(2,j--);//通过变换num的值来对应数组中的1
            if(tem == 1)
                a[i--] = 1;
            else
                a[i--] = 0;
        }
        return 1;
    }
    bool set_product_state(int state)
    {
        product_state = state;
        if (state == 0)
            return false;
        else if(state == 1)
            return true;
    }

};
workshop::workshop():worktype(0),x(0),y(0),left_produce_time(0),material_state(0),product_state(0),number(0){}

#endif //CODECRAFTSDK_WORKSHOP_H
