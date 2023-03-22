//
// Created by 10259 on 2023/3/20.
//

#ifndef CODECRAFTSDK_DEAL_H
#define CODECRAFTSDK_DEAL_H


#include "../Object/Robot.h"
#include "../Object/Workshop.h"
#include "../Object/material.h"
class Deal {
public:
    static vector<int> calculateMaterialNum(int materialState);
    static bool readUntilOK(Robot robots[], Workshop workshops[], double &reward, int &workshopCount);
    static double distance(Position p1, Position p2);
    static bool isNearWorkshop(Robot robot, Workshop workshops[], int count);
    static vector<int> getMaterialNum(const Workshop& workshop);
    static void interactWithWorkshop(Robot &robot, Workshop workshops[], material material[],int workshopCount, int flags[],int framesid,double &reward);
};


#endif //CODECRAFTSDK_DEAL_H
