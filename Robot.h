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
    double toward;  // 朝向
    Position position;  //机器人所处坐标
    int frameid;//记录拿到物品时的帧数
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

    void set_frameid(int frameid);
    int get_frameid() const;

};


#endif //CODECRAFTSDK_ROBOT_H
