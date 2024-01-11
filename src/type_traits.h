//
// Created by yangcsky on 2023/11/25.
//

#ifndef MYSTL_TYPE_TRAITS_H
#define MYSTL_TYPE_TRAITS_H

// 这个头文件用于提取类型信息
#include <type_traits>

namespace mystl{
    // 辅助结构体
    template <class T, T v>
    struct m_integral_constant {
        static constexpr T value = v;
    };

    template <bool b>
    using m_bool_constant = m_integral_constant<bool, b>;

    typedef m_bool_constant<true> m_true_type;
    typedef m_bool_constant<false> m_false_type;

    /*********************************************************************/
    // type traits
    // is_pair
    // 前置声明开始
    template <class T1, class T2>
    struct pair;
    // 前置声明结束

    template <class T>
    struct is_pair : mystl::m_false_type {};

    template <class T1, class T2>
    struct is_pair<mystl::pair<T1, T2>> : mystl::m_true_type {};

} // namespace mystl




#endif //MYSTL_TYPE_TRAITS_H
