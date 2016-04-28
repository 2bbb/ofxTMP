//
//  ofxTMPTypeTraits.h
//
//  Created by ISHII 2bit on 2016/04/28.
//
//

#pragma once

#include <type_traits>
#include <array>

namespace ofx {
    namespace TMP {
        struct default_traits {
            static constexpr size_t size = 1;
            static constexpr bool has_subscript_operator = false;
        };
        
        template <size_t size, typename T = float>
        struct array_traits {
            using inner_type = T;
            static constexpr size_t size = size;
            static constexpr bool has_subscript_operator = true;
        };
        
        template <typename T>
        struct type_traits : default_traits {
            using inner_type = T;
        };
        
        template <typename T>
        struct type_traits<ofColor_<T>> : array_traits<4, T> {};
        
        template <>
        struct type_traits<ofVec2f> : array_traits<2> {};
        
        template <>
        struct type_traits<ofVec3f> : array_traits<3> {};
        
        template <>
        struct type_traits<ofVec4f> : array_traits<4> {};
        
        template <>
        struct type_traits<ofQuaternion> : array_traits<4> {};
        
        template <>
        struct type_traits<ofMatrix3x3> : array_traits<9> {
            static constexpr bool has_subscript_operator = false; // because don't has "float operator[](int n) const"
        };
        
        template <>
        struct type_traits<ofMatrix4x4> : array_traits<16> {
            static constexpr bool has_subscript_operator = false;
        };
        
        template <>
        struct type_traits<ofRectangle> {
            using inner_type = float;
            static constexpr size_t size = 4;
            static constexpr bool has_subscript_operator = false;
        };
        
        template <typename T, size_t array_size>
        struct type_traits<T[array_size]> {
            using inner_type = T;
            static constexpr size_t size = type_traits<T>::size * array_size;
            static constexpr bool has_subscript_operator = true;
        };
        
        template <typename T, size_t array_size>
        struct type_traits<std::array<T, array_size>> {
            using inner_type = T;
            static constexpr size_t size = type_traits<T>::size * array_size;
            static constexpr bool has_subscript_operator = true;
        };
    };
};
