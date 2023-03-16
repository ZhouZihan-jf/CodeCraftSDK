#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include "workshop.cpp"

using namespace std;
int framenum = 1,totalmoney = 0,workshopnum = 0;
int initialization(int count,char *line)
{
    const char *d = " ";
    const char *e = "\n";
    char *p,*q;
    int num = 1;
    if(count == 1)//对帧序号和当前金钱数的初始化
    {
        q = strtok(line,e);
        p = strtok(q,d);
        while(p&&q)
        {
            printf("%s\n",p);
            stringstream get(p);
            if(num++ == 1)
                get >> framenum;
            if(num == 2)
                get >> totalmoney;
            p = strtok(NULL,d);
        }
    }
    if(count == 2)//对工作台的初始化
    {
        q = strtok(line,e);
        p = strtok(q,d);
        stringstream get(p);
        while(p&&q)
        {
            printf("%s\n",p);
            p = strtok(NULL,d);
        }
        get >> workshopnum;
    }
    return 1;
}
bool readUntilOK() {
    char line[1024];
    FILE *stream;
    int count = 1,i = 1,j = 1;
    stream = fopen("C:\\Users\\huawei\\Desktop\\huawei\\data.txt","r");
    while (fgets(line, sizeof line, stream)) {//从标准输入中读取一行，并存放在line中
        if (line[0] == 'O' && line[1] == 'K') {
            return true;
            break;
        }
        if(count < 3)
        {
            initialization(count++,line);
            continue;
        }
        if(count >=3 && i <= workshopnum)
        {
            create_workshop(i++,line);
            continue;
        }
//        if(count >= 2 + workshopnum)
//        {
//            create_robot(j++,line);
//            continue;
//        }
    }
    return false;
}

int main() {
    readUntilOK();
    puts("OK");//标准输出“ok”并换行
    fflush(stdout);//冲洗流中的信息，缓冲区内的数据写回标准输出的文件中
    int frameID;//帧的id号
    while (scanf("%d", &frameID) != EOF) {//文件读入还没结束时进入循环
        readUntilOK();
        printf("%d\n", frameID);
        int lineSpeed = 3;
        double angleSpeed = 1.5;
        for(int robotId = 0; robotId < 4; robotId++){
            printf("forward %d %d\n", robotId, lineSpeed);
            printf("rotate %d %f\n", robotId, angleSpeed);
        }
        printf("OK\n", frameID);
        fflush(stdout);
    }
    return 0;
}
