//
// Created by 10259 on 2023/3/19.
//

#ifndef CODECRAFTSDK_WORKSHOP_H
#define CODECRAFTSDK_WORKSHOP_H


#include "Position.h"
#include <vector>
using namespace std;

class Workshop {
    int workshopId; // 工作台编号
    int workType;  // 工作台类型
    Position position;  // 所处的位置
    int leftProduceTime;  // 剩余生产时间
    vector<int> materialNum; // 已有原材料类型
    vector<int> needMaterialNum; // 需要原材料类型
    int productState;  // 产品格状态，只有0和1
    int number;  // 工作台自身编号
public:
    Workshop();
    Workshop(int workType, const Position &position, const vector<int> &needMaterialNum);
    Workshop(int workType, const vector<int> &needMaterialNum);
    Workshop(int workType, const Position &position);
    Workshop(int workType);

    virtual ~Workshop();

    const vector<int> &getNeedMaterialNum() const;
    void setNeedMaterialNum(int workType);

    int getWorkType() const;
    void setWorkType(int workType);

    const Position &getPosition() const;
    void setPosition(const Position &position);

    int getLeftProduceTime() const;
    void setLeftProduceTime(int leftProduceTime);

    int getProductState() const;
    void setProductState(int productState);

    int getNumber() const;
    void setNumber(int number);

    const vector<int> &getMaterialNum() const;
    void setMaterialNum(const vector<int> &materialNum);

    int getWorkshopId() const;

    void setWorkshopId(int workshopId);
};


#endif //CODECRAFTSDK_WORKSHOP_H
