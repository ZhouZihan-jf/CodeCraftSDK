//
// Created by 10259 on 2023/3/19.
//

#ifndef CODECRAFTSDK_ROBOT_H
#define CODECRAFTSDK_ROBOT_H


#include "LineSpeed.h"
#include "Position.h"

class Robot {
private:
    int workshopId{};  // 所处工作台id
    int itemType{};  // 携带物品类型
    float timeWorth{};  // 时间价值系数
    float collisionWorth{};  // 碰撞价值系数
    float rotate{};  // 角速度
    LineSpeed lineSpeed{};  // 线速度
    float toward{};  // 朝向
    Position position{};  //机器人所处坐标
public:
    Robot();
    Robot(const Position &position);

    int getWorkshopId() const;
    void setWorkshopId(int workshopId);

    int getItemType() const;
    void setItemType(int itemType);

    float getTimeWorth() const;
    void setTimeWorth(float timeWorth);

    float getCollisionWorth() const;
    void setCollisionWorth(float collisionWorth);

    float getRotate() const;
    void setRotate(float rotate);

    const LineSpeed &getLineSpeed() const;
    void setLineSpeed(const LineSpeed &lineSpeed);

    float getToward() const;
    void setToward(float toward);

    const Position &getPosition() const;

    void setPosition(const Position &position);

};


#endif //CODECRAFTSDK_ROBOT_H
