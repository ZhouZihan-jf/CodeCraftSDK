//
// Created by 10259 on 2023/3/19.
//
#include <iostream>
#include "../Object/Robot.h"
#include "../Object/Workshop.h"
using namespace std;


bool readUntilOK(Robot robots[], Workshop workshops[]) {
    char line[1024];
    while (fgets(line, sizeof line, stdin)) {
        if (line[0] == 'O' && line[1] == 'K') {
            return true;
        }
        //do something
    }
    return false;
}




/* 根据materialState的值，将其转化为二进制，然后将二进制中的1的位置记录下来，即为materialNum的值
 * 例如：materialState = 5，即101，那么materialNum = {0, 2}
 *
Workshop::Workshop(int workType, const Position &position, int leftProduceTime, int materialState, int productState,
                   int number) : workType(workType), position(position), leftProduceTime(leftProduceTime),
                   productState(productState), number(number) {
    int arr[100], i=0;
    while (materialState){
        arr[i] = materialState % 2;
        materialState /= 2;
        i++;
    }

    int count = 0;
    for(int j=i; j>=0; j--){
        if(arr[j] == 1){
            Workshop::materialNum.push_back(count);
        } else{
            count ++;
        }
    }

}
 */