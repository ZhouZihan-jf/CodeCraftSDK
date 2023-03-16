#include <math.h>
#define PI acos(-1)
#ifndef CODECRAFTSDK_ROBOT_H
#define CODECRAFTSDK_ROBOT_H
class linspeed
{
private:
    float x,y;
public:
    linspeed();
    float set_x(float x)
    {
        x = x;
        return 1;
    }
    float set_y(float y)
    {
        y = y;
        return 1;
    }
};
linspeed::linspeed():x(0),y(0){}
class robot {
private:
    int workshopid;//所处工作台id
    int item_type;//携带物品类型
    float time_worth;//时间价值系数
    float collision_worth;//碰撞价值系数
    float anglespeed;//角速度
    linspeed linespeed;//线速度
    float rotate;//转向
    float x,y;//机器人所处的坐标
    int number;//机器人自身编号
public:
    robot();
    int set_workshopid(int id,int k)//设置所处工作台id，目前想法：与各个工作台之间的距离实时更新，并且添加对应的工作台操作
    {
        workshopid = id;
        if (workshopid == -1)
            return 0;
        else if (workshopid >= 0 && workshopid < k)
            return 1;
        else
            return -1;
    }
    int set_itemtype(int type)//设置机器人携带物品的类型
    {
        item_type = type;
        int item[8] ={0};
        if (item_type == 0)
        {
            //print("未携带物品");
            return 0;
        }
        else if (item_type >= 1 && item_type <= 7)
        {
            //print("携带相应的物品“);
            item[item_type] = 1;
            return item_type;
        }
    }
    float set_timeworth(float time)//设置时间价值系数
    {
        time_worth = time;
        if(time_worth == 0)
        {
            //print("未携带物品”);
            return 0;
        }
        else if(time_worth >= 0.8 && time_worth <= 1)
        {
            return time_worth;
        }
    }
    float set_collision(float c)//设置碰撞价值系数
    {
        collision_worth = c;
        if(collision_worth == 0)
        {
            //print("未携带物品”);
            return 0;
        }
        else if(collision_worth >= 0.8 && collision_worth <= 1)
        {
            return collision_worth;
        }
    }
    float set_anglespeed(float aspeed)//设置角速度
    {
        anglespeed = aspeed;
        //正数表示逆时针方向，负数表示顺时针方向
    }
    float set_linespeed(float a,float b)//设置线速度
    {
        linespeed.set_x(a);
        linespeed.set_y(b);
        return 1;
    }
    float set_rotate(float r)//设置初始的转向
    {
        rotate = r;
        if (rotate == 0)
        {
            //print("turn right!")
            return 0;
        }
        else if (rotate > PI || rotate < -PI)
            return -1;
        else {
            if (rotate == PI / 2) {
                //print("turn straight up!")
                return rotate;
            }
            else if (rotate == -(PI/2))
            {
                //print("turn straight down!")
                return rotate;
            }
            else
                return rotate;
        }
    }
    float set_location(float a,float b)//设置坐标
    {
        x = a;
        y = b;
        return 0;
    }
    int set_number(int n)//设置每个机器人的编号
    {
        number = n;
        return 0;
    }
};

robot::robot():workshopid(0),item_type(0),time_worth(0),collision_worth(0),anglespeed(0), linespeed(0,0),rotate(0),x(0),y(0),number(0){}

#endif //CODECRAFTSDK_ROBOT_H
