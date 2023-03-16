#include <iostream>
using namespace std;

bool readUntilOK() {  // 读取ok信号
    char line[1024];
    while (fgets(line, sizeof line, stdin)) {
        if (line[0] == 'O' && line[1] == 'K') {
            return true;
        }
        //do something
    }
    return false;
}

void readFrame(){  //读取帧

}




int main() {
    readUntilOK();  // 读判题器传的信息
    puts("OK");  // 回传确认信息
    fflush(stdout);
    int frameID;
    while (scanf("%d", &frameID) != EOF) {  // 判题器给我帧信息
        readUntilOK();
        printf("%d\n", frameID);  // 第一行输出帧id

        int lineSpeed = 3;  // 线速度
        double angleSpeed = 1.5;  // 角速度
        for(int robotId = 0; robotId < 4; robotId++){  // 有四个机器人
            printf("forward %d %d\n", robotId, lineSpeed);  // 前进forward指令
            printf("rotate %d %f\n", robotId, angleSpeed);  // 旋转rotate指令
            printf("buy %d\n",robotId);                     // 购买buy指令
            printf("sell %d\n",robotId);                    // 卖出sell指令
            printf("destroy %d\n",robotId);                 // 销毁destroy指令
        }
        printf("OK\n", frameID);  // 程序每一次应答以ok结尾
        fflush(stdout);
    }
    return 0;
}
