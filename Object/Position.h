//
// Created by 10259 on 2023/3/19.
//

#ifndef CODECRAFTSDK_POSITION_H
#define CODECRAFTSDK_POSITION_H


class Position {
private:
    float x, y;
public:
    Position();
    Position(float x, float y);
    void setPosition(float x, float y);

    float getX() const;
    float getY() const;

};


#endif //CODECRAFTSDK_POSITION_H
