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
    static bool readUntilOK(Robot robots[], Workshop workshops[], int &reward);
    static double distance(Position p1, Position p2);
    static bool isNearWorkshop(Robot robot, const Workshop& workshop);
    static vector<int> getMaterialNum(const Workshop& workshop);
    static void interactWithWorkshop(Robot &robot, Workshop workshops[], int flags[]);
};


#endif //CODECRAFTSDK_DEAL_H
