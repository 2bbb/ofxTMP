//
//  ofxTMPSequence.h
//
//  Created by ISHII 2bit on 2016/04/28.
//
//

#pragma once

namespace ofx {
    namespace TMP {
        namespace sequences {
            template <typename type, type ... ns>
            struct integer_sequence {
                using value_type = type;
                static constexpr std::size_t size = sizeof...(ns);
            };
            
            namespace detail {
                template <typename integer_type, integer_type n, integer_type ... ns>
                struct make_integer_sequence {
                    struct sequence_wrapper { using type = integer_sequence<integer_type, ns ...>; };
                    using type = get_type<conditional<
                        n == 0,
                        sequence_wrapper,
                        detail::make_integer_sequence<integer_type, n - 1, n - 1, ns ...>
                    >>;
                };
            };
            
            template <typename type, type n>
            using make_integer_sequence = detail::make_integer_sequence<type, n>;
            
            template <std::size_t ... ns>
            using index_sequence = integer_sequence<std::size_t, ns ...>;
            
            template <std::size_t n>
            using make_index_sequence = make_integer_sequence<std::size_t, n>;
            
            template <typename... types>
            using index_sequence_for = make_index_sequence<sizeof...(types)>;
        };
        using namespace sequences;
    };
};