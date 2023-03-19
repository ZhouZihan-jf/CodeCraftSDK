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

        int count = 0;
        for(char i : line){
            count++;
            // 记录x，y；
            if(i == '.'){  // 如果遇到.就跳过
                continue;
            }
            if(i == 'A'){  // 遇到机器人了
                Robot robot = Robot();

            }
            if(i >= '1' && i <= '9'){  // 遇到台子了
                Workshop workshop = Workshop();
            }
        }

    }


}

