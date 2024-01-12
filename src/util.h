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
        // 完美转发，接受左值，返回的也是左值
        return static_cast<T&&>(arg);
    }
    template <class T>
    T&& forward(typename std::remove_reference<T>::type&& arg) noexcept {
        // 完美转发，接受的是万能引用，输入的是左值就返回左值，输入的是右值就返回右值
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
        first_type first; // 保存第一个数据
        second_type second; // 保存第二个数据
        // 默认构造
        template <class Other1=Ty1, class Other2=Ty2,
                typename = typename std::enable_if<
                        std::is_default_constructible<Other1>::value &&
                        std::is_default_constructible<Other2>::value,void>::type>
        constexpr pair() : first(), second() {
            // enable_if用于构建需要根据不同的类型的条件实例化不同的模板,第一个模板参数是true，第二个模板参数默认void
        }

        // 对这个type隐式可构造的
        template<class U1 = Ty1, class U2 = Ty2, typename std::enable_if<
                std::is_copy_constructible<U1>::value && std::is_copy_constructible<U2>::value &&
                std::is_convertible<const U1&, Ty1>::value &&
                std::is_convertible<const U2&, Ty2>::value, int>::type = 0>
        constexpr pair(const Ty1& a, const Ty2& b) : first(a), second(b) {}

        // 对这个type是显示可构造的
        template <class U1 = Ty1, class U2 = Ty2,
                typename std::enable_if<
                        std::is_copy_constructible<U1>::value &&
                        std::is_copy_constructible<U2>::value &&
                        (!std::is_convertible<const U1&, Ty1>::value ||
                         !std::is_convertible<const U2&, Ty2>::value), int>::type = 0>
        explicit constexpr pair(const Ty1& a, const Ty2& b)
                : first(a), second(b)
        {
        }

        pair(const pair& rhs) = default;
        pair(pair&& rhs) = default;

        // 对其他type的隐式构造
        template <class Other1, class Other2,
                typename std::enable_if<
                        std::is_constructible<Ty1, Other1>::value &&
                        std::is_constructible<Ty2, Other2>::value &&
                        std::is_convertible<Other1&&, Ty1>::value &&
                        std::is_convertible<Other2&&, Ty2>::value, int>::type = 0>
        constexpr pair(Other1&& a, Other2&& b)
                : first(mystl::forward<Other1>(a)),
                  second(mystl::forward<Other2>(b))
        {
        }

        // 对其他type的显示构造
        template <class Other1, class Other2,
                typename std::enable_if<
                        std::is_constructible<Ty1, Other1>::value &&
                        std::is_constructible<Ty2, Other2>::value &&
                        (!std::is_convertible<Other1, Ty1>::value ||
                         !std::is_convertible<Other2, Ty2>::value), int>::type = 0>
        explicit constexpr pair(Other1&& a, Other2&& b)
                : first(mystl::forward<Other1>(a)),
                  second(mystl::forward<Other2>(b))
        {
        }

        // 对其他pair的隐式构造
        template <class Other1, class Other2,
                typename std::enable_if<
                        std::is_constructible<Ty1, const Other1&>::value &&
                        std::is_constructible<Ty2, const Other2&>::value &&
                        std::is_convertible<const Other1&, Ty1>::value &&
                        std::is_convertible<const Other2&, Ty2>::value, int>::type = 0>
        constexpr pair(const pair<Other1, Other2>& other)
                : first(other.first),
                  second(other.second)
        {
        }

        // 对其他pair的显示构造
        template <class Other1, class Other2,
                typename std::enable_if<
                        std::is_constructible<Ty1, const Other1&>::value &&
                        std::is_constructible<Ty2, const Other2&>::value &&
                        (!std::is_convertible<const Other1&, Ty1>::value ||
                         !std::is_convertible<const Other2&, Ty2>::value), int>::type = 0>
        explicit constexpr pair(const pair<Other1, Other2>& other)
                : first(other.first),
                  second(other.second)
        {
        }

        // 对其他pair的隐式构造
        template <class Other1, class Other2,
                typename std::enable_if<
                        std::is_constructible<Ty1, Other1>::value &&
                        std::is_constructible<Ty2, Other2>::value &&
                        std::is_convertible<Other1, Ty1>::value &&
                        std::is_convertible<Other2, Ty2>::value, int>::type = 0>
        constexpr pair(pair<Other1, Other2>&& other)
                : first(mystl::forward<Other1>(other.first)),
                  second(mystl::forward<Other2>(other.second))
        {
        }

        // 对其他pair的显示构造
        template <class Other1, class Other2,
                typename std::enable_if<
                        std::is_constructible<Ty1, Other1>::value &&
                        std::is_constructible<Ty2, Other2>::value &&
                        (!std::is_convertible<Other1, Ty1>::value ||
                         !std::is_convertible<Other2, Ty2>::value), int>::type = 0>
        explicit constexpr pair(pair<Other1, Other2>&& other)
                : first(mystl::forward<Other1>(other.first)),
                  second(mystl::forward<Other2>(other.second))
        {
        }

        // pair的拷贝复制符号的重载运算符
        pair& operator=(const pair& rhs)
        {
            if (this != &rhs)
            {
                first = rhs.first;
                second = rhs.second;
            }
            return *this;
        }

        // pair的移动赋值重载运算符‘=’
        pair& operator=(pair&& rhs)
        {
            if (this != &rhs)
            {
                first = mystl::move(rhs.first);
                second = mystl::move(rhs.second);
            }
            return *this;
        }

        // 其他pair的拷贝复制运算符重载
        template <class Other1, class Other2>
        pair& operator=(const pair<Other1, Other2>& other)
        {
            first = other.first;
            second = other.second;
            return *this;
        }

        // 其他pair的移动赋值运算符重载
        template <class Other1, class Other2>
        pair& operator=(pair<Other1, Other2>&& other)
        {
            first = mystl::forward<Other1>(other.first);
            second = mystl::forward<Other2>(other.second);
            return *this;
        }

        ~pair() = default; // 析构函数default

        // swap
        void swap(pair& other)
        {
            if (this != &other)
            {
                mystl::swap(first, other.first);
                mystl::swap(second, other.second);
            }
        }
    };

    // 重载比较操作符
    template <class Ty1, class Ty2>
    bool operator==(const pair<Ty1, Ty2>& lhs, const pair<Ty1, Ty2>& rhs)
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template <class Ty1, class Ty2>
    bool operator<(const pair<Ty1, Ty2>& lhs, const pair<Ty1, Ty2>& rhs)
    {
        return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
    }

    template <class Ty1, class Ty2>
    bool operator!=(const pair<Ty1, Ty2>& lhs, const pair<Ty1, Ty2>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class Ty1, class Ty2>
    bool operator>(const pair<Ty1, Ty2>& lhs, const pair<Ty1, Ty2>& rhs)
    {
        return rhs < lhs;
    }

    template <class Ty1, class Ty2>
    bool operator<=(const pair<Ty1, Ty2>& lhs, const pair<Ty1, Ty2>& rhs)
    {
        return !(rhs < lhs);
    }

    template <class Ty1, class Ty2>
    bool operator>=(const pair<Ty1, Ty2>& lhs, const pair<Ty1, Ty2>& rhs)
    {
        return !(lhs < rhs);
    }

    // 重载 mystl 的 swap
    template <class Ty1, class Ty2>
    void swap(pair<Ty1, Ty2>& lhs, pair<Ty1, Ty2>& rhs)
    {
        lhs.swap(rhs);
    }

    // 全局函数，让两个数据成为一个 pair
    template <class Ty1, class Ty2>
    pair<Ty1, Ty2> make_pair(Ty1&& first, Ty2&& second)
    {
        return pair<Ty1, Ty2>(mystl::forward<Ty1>(first), mystl::forward<Ty2>(second));
    }
}



#endif //MYSTL_UTIL_H
