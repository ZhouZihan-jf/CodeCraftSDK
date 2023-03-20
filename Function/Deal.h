//
// Created by 10259 on 2023/3/20.
//

#ifndef CODECRAFTSDK_DEAL_H
#define CODECRAFTSDK_DEAL_H


#include "../Object/Robot.h"
#include "../Object/Workshop.h"

class Deal {
public:
    static bool initialization(Robot robots[], Workshop workshops[]);
    static vector<int> calculateMaterialNum(int materialState);
    bool readUntilOK(Robot robots[], Workshop workshops[], int &reward);
    double distance(Position p1, Position p2);
    bool isNearWorkshop(Robot robot, const Workshop& workshop);
    vector<int> getMaterialNum(const Workshop& workshop);
    void interactWithWorkshop(Robot &robot, Workshop workshops[], int flags[]);
};


#endif //CODECRAFTSDK_DEAL_H
