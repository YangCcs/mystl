//
// Created by yangcsky on 2023/11/25.
//

#ifndef MYSTL_UTIL_H
#define MYSTL_UTIL_H

// 这个文件包含一些通用工具，包括move，forward，swap等函数，以及pair等

#include <cstddef>
#include "type_traits.h"

namespace mystl {
    // move
    template <class T>
    // typename关键字用来告诉编译器这个一个类型，而不是一个静态成员变量或者函数
    typename std::remove_reference<T>::type&& move(T&& arg) noexcept {
        // 万能引用参数，无论传入的参数是左值或者右值，一律转化为右值并传出
        return static_cast<typename std::remove_reference<T>::type&&>(arg);
    }

    // forward
    template <class T>
    T&& forward(typename std::remove_reference<T>::type& arg) noexcept {
        // 输入左值引用，返回右值引用
        return static_cast<T&&>(arg);
    }
    template <class T>
    T&& forward(typename std::remove_reference<T>::type&& arg) noexcept {
        // 输入万能引用，返回右值引用
        return static_cast<T&&>(arg);
    }

    // swap
    template <class Tp>
    void swap(Tp& lhs, Tp& rhs) {
        auto tmp(mystl::move(lhs));
        lhs = mystl::move(rhs);
        rhs = mystl::move(tmp);
    }
    template <class ForwardIter1, class ForwardIter2>
    ForwardIter2 swap_range(ForwardIter1 first1, ForwardIter1 last1, ForwardIter2 first2) {
        for (; first1 != last1; ++first1, (void)++first2) {
            mystl::swap(*first1, *first2);
        }
        return first2;
    }
    template <class Tp, size_t N>
    void swap(Tp(&a)[N], Tp(&b)[N]) {
        mystl::swap_range(a, a + N, b);
    }

    // -------------------------------------------------------------------------------

    // pair
    // 结构体模板 pair
    // 两个模板参数分别表示两个数据的类型，用first和second来分别取出第一个数据和第二个数据
    template <class Ty1, class Ty2>
    struct pair {
            typedef Ty1 first_type;
            typedef Ty2 second_type;
            first_type first;
            second_type second;
            // 默认构造
            template <class Other1=Ty1, class Other2=Ty2,
                    typename = typename std::enable_if<std::is_default_constructible<Other1>::value &&
                            std::is_default_constructible<Other2>::value, void>::type> constexpr pair() : first(), second() {
                                // enable_if用于构建需要根据不同的类型的条件实例化不同的模板,第一个
                            }
        };
}



#endif //MYSTL_UTIL_H
