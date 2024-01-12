//
// Created by yangcsky on 2024/1/11.
//

#include <string>
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
struct S1{
    typedef T type; // using type = T;
};

template <bool, typename T = void>
struct _enable_if {

};

// 偏特化
template <typename Tp>
struct _enable_if<true, Tp> {
    typedef Tp type;
};

template <bool Bp, class Tp = void>
using _enable_if_t = typename _enable_if<Bp, Tp>::type;

// 函数示例
template <class T>
typename _enable_if<(sizeof(T) > 2)>::type func1() {}

/*
 * enable_if中的条件特化可以看成一个条件分支语句，在编译期间就能判断条件是否成立
 * 但是代码if-else中的条件分支语句，必须执行时才知道条件是否成立
 * */

int main() {
    S1<int>::type a = 666; // int a = 666
    cout << a << endl;

    S1<string>::type b = "yangcs"; // string = "yangcs"
    cout << b << endl;

    _enable_if<true>::type* c = nullptr; // void* c = nullptr
    cout << c << endl;

    _enable_if<true, int>::type d = 123; // int d = 123;
    cout << d << endl;

    func1<int>(); // bool被推断为true，T为void，编译通过
    // func1<char>(); // bool被推断为false，没有对应的【type】，错误

    return 0;
}
