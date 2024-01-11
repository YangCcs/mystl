//
// Created by yangcsky on 2023/11/25.
//

#include "stdcpp.h"
#include <thread>

int main() {
    int a = 5;
    cout << a << endl;

    vector<int> vec = {5};
    for (vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter++) {
        cout << *iter << endl;
    }

    // priority_queue<int, vector<int>, less<>> priorityQueue; // 默认是大顶堆啊
    priority_queue<int, vector<int>, greater<>> priorityQueue;
    priorityQueue.push(1);
    priorityQueue.push(2);
    priorityQueue.push(3);
    cout << priorityQueue.top() << endl;


}