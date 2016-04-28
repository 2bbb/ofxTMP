//
//  ofxTMPUtils.h
//
//  Created by ISHII 2bit on 2016/04/28.
//
//

#pragma once

#include <type_traits>
#include <tuple>
#include <functional>

#if __cplusplus < 201103L
#   error all you need is C++11 (or later)
#elif __cplusplus < 201402L
#   define bbb_is_cpp11 true
#   define bbb_is_cpp14 false
#else
#   define bbb_is_cpp11 true
#   define bbb_is_cpp14 true
#endif

namespace ofx {
    namespace TMP {
        constexpr bool is_cpp11() { return bbb_is_cpp11; }
        constexpr bool is_cpp14() { return bbb_is_cpp14; }
        
        template <typename T>
        using get_type = typename T::type;
        
        template <bool b, typename T = void>
        using enable_if = get_type<std::enable_if<b, T>>;
        
        template <bool b, typename T, typename F>
        using conditional = get_type<std::conditional<b, T, F>>;
        
        template <typename T, typename U>
        constexpr bool is_same() { return std::is_same<T, U>::value; };
        
        template <typename T>
        constexpr bool is_const() {
            return std::is_const<T>::value;
        }
        
        template <typename T>
        constexpr bool is_number() {
            return std::is_arithmetic<T>::value;
        }
        
        template <typename T>
        constexpr bool is_integer() {
            return std::is_integral<T>::value;
        }
        
        template <typename T>
        constexpr bool is_float() {
            return std::is_floating_point<T>::value;
        }
        
        template <typename T>
        using remove_const_reference_if_number = get_type<std::conditional<
            is_number<T>(),
            get_type<std::remove_reference<
                get_type<std::remove_const<T>>
            >>,
            T
        >>;
        
        template <typename T>
        using add_const_reference_if_not_number = get_type<std::conditional<
            !is_number<T>(),
            get_type<std::add_const<
                get_type<std::add_lvalue_reference<T>>
            >>,
            T
        >>;
        
        template <std::size_t index, typename ... arguments>
        using type_at = get_type<std::tuple_element<index, std::tuple<arguments ...>>>;
        
        template <bool condition, template <typename ...> class t, template <typename ...> class f>
        struct template_conditional {
            template <typename ... arguments>
            using type = get_type<std::conditional<condition, t<arguments ...>, f<arguments ...>>>;
        };
    };
};