//
// Created by 10259 on 2023/3/19.
//
#include <iostream>
using namespace std;


bool readUntilOK() {
    char line[1024];
    while (fgets(line, sizeof line, stdin)) {
        if (line[0] == 'O' && line[1] == 'K') {
            return true;
        }
        //do something
    }
    return false;
}
/*
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