//
//  ofxTMPAlias.h
//
//  Created by ISHII 2bit on 2016/04/29.
//
//

#pragma once

namespace ofx {
    namespace TMP {
        template <typename>
        struct alias {};
        
        namespace detail {
            template <typename T>
            struct remove_alias { using type = T; };
            template <typename T>
            struct remove_alias<alias<T>> { using type = T; };
            
            template <typename T>
            struct remove_aliases { using type = T; };
            template <typename T>
            struct remove_aliases<alias<T>> { using type = typename remove_alias<T>::type; };
        };
        
        template <typename T>
        using remove_alias = get_type<TMP::detail::remove_alias<T>>;
        template <typename T>
        using remove_aliases = get_type<TMP::detail::remove_aliases<T>>;
    };
};
