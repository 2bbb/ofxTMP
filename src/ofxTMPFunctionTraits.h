//
//  ofxTMPFunctionTraits.h
//  ofxTMPExample
//
//  Created by ISHII 2bit on 2016/04/28.
//
//

#include <type_traits>
#include <tuple>
#include <functional>

namespace ofx {
    namespace TMP {
        namespace function_info {
            namespace detail {
                template <typename ret, typename ... arguments>
                struct function_traits {
                    static constexpr std::size_t arity = sizeof...(arguments);
                    using result_type = ret;
                    using arguments_types_tuple = std::tuple<arguments ...>;
                    template <std::size_t index>
                    using argument_type = type_at<index, arguments ...>;
                    using function_type = std::function<ret(arguments ...)>;
                    template <typename function_t>
                    static constexpr function_type cast(function_t f) {
                        return static_cast<function_type>(f);
                    }
                };
            };
            
            template <typename T>
            struct function_traits : public function_traits<decltype(&T::operator())> {};
            
            template <typename class_type, typename ret, typename ... arguments>
            struct function_traits<ret(class_type::*)(arguments ...) const>
            : detail::function_traits<ret, arguments ...> {};
            
            template <typename class_type, typename ret, typename ... arguments>
            struct function_traits<ret(class_type::*)(arguments ...)>
            : detail::function_traits<ret, arguments ...> {};
            
            template <typename ret, typename ... arguments>
            struct function_traits<ret(*)(arguments ...)>
            : detail::function_traits<ret, arguments ...> {};
            
            template <typename ret, typename ... arguments>
            struct function_traits<ret(arguments ...)>
            : detail::function_traits<ret, arguments ...> {};
            
            template <typename ret, typename ... arguments>
            struct function_traits<std::function<ret(arguments ...)>>
            : detail::function_traits<ret, arguments ...> {};
            
            template<typename T>
            using result_type = typename function_traits<T>::result_type;
            
            template<typename T>
            using arguments_types_tuple = typename function_traits<T>::arguments_types_tuple;
            
            template<typename T, std::size_t index>
            using argument_type = typename function_traits<T>::template argument_type<index>;
            
            template<typename T>
            struct arity {
                static constexpr std::size_t value = function_traits<T>::arity;
            };
            
            template <typename patient>
            struct has_call_operator {
                template <typename inner_patient, decltype(&inner_patient::operator())> struct checker {};
                template <typename inner_patient> static std::true_type  check(checker<inner_patient, &inner_patient::operator()> *);
                template <typename>               static std::false_type check(...);
                using type = decltype(check<patient>(nullptr));
                static constexpr bool value = type::value;
            };
            
            template <typename patient>
            constexpr bool is_callable(const patient &) {
                return std::is_function<patient>::value || has_call_operator<patient>::value;
            };
            
            template <typename function_t>
            constexpr auto cast_lambda(function_t f)
            -> typename function_traits<function_t>::function_type {
                return static_cast<typename function_traits<function_t>::function_type>(f);
            }
        };
        using namespace function_info;
    };
};
