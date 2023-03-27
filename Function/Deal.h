//
// Created by 10259 on 2023/3/20.
//

#ifndef CODECRAFTSDK_DEAL_H
#define CODECRAFTSDK_DEAL_H


#include "../Object/Robot.h"
#include "../Object/Workshop.h"

class Deal {
public:
    static vector<int> calculateMaterialNum(int materialState);
    static bool readUntilOK(Robot robots[], Workshop workshops[], int &reward, int &workshopCount);
    static double distance(Position p1, Position p2);
    static int isNearWorkshop(Robot robot, Workshop workshops[], int workshopCount);
    static vector<int> getMaterialNum(const Workshop& workshop);
    static void interactWithWorkshop(Robot &robot, Workshop workshops[], int workshopCount, int flags[]);
    static int isRightDirection(Robot &robot, const Workshop& workshop);
    static void action(Robot &robot, const Robot robots[], const Workshop& workshop, double& lineSpeed, double& rotateSpeed);
    static Workshop findTargetWorkshop(Robot robot, Workshop workshops[], vector<Workshop>& w1, vector<Workshop>& w2,  int workshopCount);
};


#endif //CODECRAFTSDK_DEAL_H
