//
// Created by 10259 on 2023/3/19.
//

#ifndef CODECRAFTSDK_POSITION_H
#define CODECRAFTSDK_POSITION_H


class Position {
private:
    double x, y;
public:
    Position();
    Position(double x, double y);
    void setPosition(double x, double y);

    double getX() const;
    double getY() const;

};


#endif //CODECRAFTSDK_POSITION_H
