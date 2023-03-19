//
// Created by 10259 on 2023/3/19.
//
#include <iostream>
#include "../Object/Robot.h"
#include "../Object/Workshop.h"
using namespace std;


bool initialization(Robot robots[], Workshop workshops[]){
    char line[1024];
    while(fgets(line, sizeof line, stdin)){
        if (line[0] == 'O' && line[1] == 'K') {
            return true;
        }

        int count = 0, i = 0;
        for(char s : line){
            count++;
            // 记录x，y；
            int x, y;
            x = count / 100;
            y = count % 100;
            auto m = float((x - 1) * 0.5 + 0.25);
            auto n = float((y - 1) * 0.5 + 0.25);

            if(s == '.'){  // 如果遇到.就跳过
                continue;
            }
            if(s == 'A'){  // 遇到机器人了
                Position position = Position(m, n);
                auto robot = Robot(position);
                robots[i] = robot;
                i++;
            }
            if(s >= '1' && s <= '9'){  // 遇到台子了
                Position position = Position(m, n);
                Workshop workshop = Workshop(s-'0', position);
                workshops[s - '0'] = workshop;
            }
        }
    }
}

