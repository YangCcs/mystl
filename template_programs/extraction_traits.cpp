//
// Created by yangcsky on 2024/1/12.
//

#include <iostream>
#include <string>

using namespace std;

/*
 * 萃取，并不是一种具体的技术或某个具体类库或函数，而是一种编程思想和模式
 * 萃取--traits（特质）
 *
 * 分类：
 * 固定萃取 - fixed traits  给定一个类型，萃取另一种类型，这两个类型之间的【对应关系】是固定的，所以称为固定萃取
 *
 * 值萃取 - value traits  给定一个类型，得到一个值
 *
 * 类型萃取 - type traits  从boost库中发展而来，实现了类型信息的提取和变换
 * */

template <typename T>
T func(const T* start, const T* end) {
    T sum{};
    for (;;) {
        sum += *start;
        if (start == end) {
            break;
        }
        start++;
    }
    return sum;
}

int main() {
    int a[] = {1, 2, 3};
    cout << func(&a[0], &a[2]) << endl;


    return 0;
}
