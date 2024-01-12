//
// Created by yangcsky on 2024/1/11.
//

#include <vector>
#include <iostream>
using namespace std;

void fun1(int& a, int&& b) {
    cout << a << "------" << b << endl;
}

// 万能引用--能绑定左值，也能绑定右值
template <class T1, class T2>
void fun2(T1&& a, T2&& b) {
    cout << a << "--------" << b << endl;
    // forward就是完美转发，解决了传左值和右值的传参问题
    fun1(std::forward<T1>(a), std::forward<T2>(b));
}

int main() {
    int a = 666;
    fun1(a, 555);
    fun2(a, 333);
}
