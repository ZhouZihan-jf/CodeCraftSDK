//
// Created by 10259 on 2023/3/19.
//

#ifndef CODECRAFTSDK_LINESPEED_H
#define CODECRAFTSDK_LINESPEED_H


class LineSpeed {
private:
    double x, y;
public:
    LineSpeed();
    LineSpeed(double x, double y);
    void setLineSpeed(double x,double y);

    double getModule() const;

};


#endif //CODECRAFTSDK_LINESPEED_H
