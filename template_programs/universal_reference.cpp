//
// Created by yangcsky on 2024/1/11.
//

#include <vector>
#include <iostream>
using namespace std;

// 万能引用
template <class T>
void fun(T &&x) {
    cout << x << endl;
}


int main() {
    int a = 666;
    fun(a);
    fun(555);


    return 0;
}