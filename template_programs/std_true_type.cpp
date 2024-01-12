//
// Created by yangcsky on 2024/1/12.
//

#include <iostream>
#include <string>

using namespace std;

class C1{};
union U1{};

int main() {
    // template<typename _Tp, _Tp __v>
    // struct integral_constant
    std::true_type t1;// using true_type =  integral_constant<bool, true>;
    cout << t1.value << endl;
    cout << false_type :: value << endl;

    cout << is_class<C1>::value << endl; // 相当于 integral_constant<bool, _is_class<T>>::value
    cout << is_union<U1>::value << endl;
}