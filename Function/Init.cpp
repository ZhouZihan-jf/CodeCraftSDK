//
// Created by 10259 on 2023/3/19.
//
#include <iostream>
#include <vector>
#include "../Object/Robot.h"
#include "../Object/Workshop.h"
using namespace std;


bool initialization(Robot robots[], Workshop workshops[]){
    char line[1024];
    vector<int> vec;

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
            auto m = double((x - 1) * 0.5 + 0.25);
            auto n = double((y - 1) * 0.5 + 0.25);

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
                int x = s - '0';
                Position position = Position(m, n);

                if(x == 4){
                    vec.push_back(1);
                    vec.push_back(2);
                    Workshop workshop = Workshop(x, position, vec);
                    workshops[x] = workshop;
                } else if(x == 5){
                    vec.push_back(1);
                    vec.push_back(3);
                    Workshop workshop = Workshop(x, position, vec);
                    workshops[x] = workshop;
                } else if(x == 6){
                    vec.push_back(2);
                    vec.push_back(3);
                    Workshop workshop = Workshop(x, position, vec);
                    workshops[x] = workshop;
                } else if(x ==7){
                    vec.push_back(4);
                    vec.push_back(5);
                    vec.push_back(6);
                    Workshop workshop = Workshop(x, position, vec);
                    workshops[x] = workshop;
                } else if(x == 8){
                    vec.push_back(7);
                    Workshop workshop = Workshop(x, position, vec);
                    workshops[x] = workshop;
                } else if(x == 9){
                    vec.push_back(1);
                    vec.push_back(2);
                    vec.push_back(3);
                    vec.push_back(4);
                    vec.push_back(5);
                    vec.push_back(6);
                    vec.push_back(7);
                    Workshop workshop = Workshop(x, position, vec);
                    workshops[x] = workshop;
                }

                vec.clear();
            }
        }
    }
}

