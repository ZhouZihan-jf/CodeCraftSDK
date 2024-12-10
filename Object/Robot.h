//
// Created by 10259 on 2023/3/19.
//

#ifndef CODECRAFTSDK_ROBOT_H
#define CODECRAFTSDK_ROBOT_H


#include "LineSpeed.h"
#include "Position.h"

class Robot {
private:
    int workshopId;  // 所处工作台id
    int itemType;  // 携带物品类型
    double timeWorth;  // 时间价值系数
    double collisionWorth;  // 碰撞价值系数
    double rotate;  // 角速度
    LineSpeed lineSpeed;  // 线速度
    double toward;  // 朝向，计算该向顺时针旋转还是向逆时针旋转
    Position position;  //机器人所处坐标
public:
    virtual ~Robot();

    Robot();
    Robot(const Position &position);

    int getWorkshopId() const;
    void setWorkshopId(int workshopId);

    int getItemType() const;
    void setItemType(int itemType);

    double getTimeWorth() const;
    void setTimeWorth(double timeWorth);

    double getCollisionWorth() const;
    void setCollisionWorth(double collisionWorth);

    double getRotate() const;
    void setRotate(double rotate);

    const LineSpeed &getLineSpeed() const;
    void setLineSpeed(const LineSpeed &lineSpeed);

    double getToward() const;
    void setToward(double toward);

    const Position &getPosition() const;

    void setPosition(const Position &position);

};


#endif //CODECRAFTSDK_ROBOT_H
