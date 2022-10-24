/*
    This header contains helper methods for comparisons of various property types.
    It is often used in conjunction with the min() and max() steps.
*/

#pragma once

#include <cstdint>
#include <boost/any.hpp>
#include <boost/core/typeinfo.hpp>
#include <sstream>

namespace gremlinxx {
    namespace comparison {

        enum C {UINT64=0, UINT32=1, INT64=2, INT32=3, FLOAT64=4, FLOAT32=5, UINT8=6, INT8=7, STRING=8, VERTEX=9};
        std::vector<std::string> C_to_string = {"UINT64", "UINT32", "INT64", "INT32", "FLOAT64", "FLOAT32", "UINT8", "INT8", "STRING", "VERTEX"};

        // Conversion from type to C type id
        template<class T>
        C C_TYPEID();

        template<>
        C C_TYPEID<uint64_t>() { return C::UINT64; }

        template<>
        C C_TYPEID<uint32_t>() { return C::UINT32; }

        template<>
        C C_TYPEID<uint8_t>() { return C::UINT8; }

        template<>
        C C_TYPEID<int64_t>() { return C::INT64; }

        template<>
        C C_TYPEID<int32_t>() { return C::INT32; }

        template<>
        C C_TYPEID<int8_t>() { return C::INT8; }

        template<>
        C C_TYPEID<double>() { return C::FLOAT64; }

        template<>
        C C_TYPEID<float>() { return C::FLOAT32; }

        template<>
        C C_TYPEID<std::string>() { return C::STRING; }

        template<>
        C C_TYPEID<Vertex*>() { return C::VERTEX; }


        // Templated function and declarations for calling less()
        template<typename T> 
        bool __call_less(boost::any a, boost::any b) {
            return std::less<T>{}(boost::any_cast<T>(a), boost::any_cast<T>(b));
        }

        template
        bool __call_less<uint64_t>(boost::any a, boost::any b);
        template
        bool __call_less<uint32_t>(boost::any a, boost::any b);
        template
        bool __call_less<uint8_t>(boost::any a, boost::any b);
        template
        bool __call_less<int64_t>(boost::any a, boost::any b);
        template
        bool __call_less<int32_t>(boost::any a, boost::any b);
        template
        bool __call_less<int8_t>(boost::any a, boost::any b);
        template
        bool __call_less<double>(boost::any a, boost::any b);
        template
        bool __call_less<float>(boost::any a, boost::any b);
        template
        bool __call_less<std::string>(boost::any a, boost::any b);
        template
        bool __call_less<Vertex*>(boost::any a, boost::any b);

        bool C_LESS(C c, boost::any a, boost::any b) {
            try {
                switch(c) {
                    case UINT64:
                        return __call_less<uint64_t>(a, b);
                    case UINT32:
                        return __call_less<uint32_t>(a, b);
                    case UINT8:
                        return __call_less<uint8_t>(a, b);
                    case INT64:
                        return __call_less<int64_t>(a, b);
                    case INT32:
                        return __call_less<int32_t>(a, b);
                    case INT8:
                        return __call_less<int8_t>(a, b);
                    case FLOAT64:
                        return __call_less<double>(a, b);
                    case FLOAT32:
                        return __call_less<float>(a, b);
                    case STRING:
                        return __call_less<std::string>(a, b);
                    case VERTEX:
                        return __call_less<Vertex*>(a, b);
                }
            } catch(const boost::bad_any_cast& ex) {
                std::stringstream sx;
                sx << ex.what() << std::endl;
                sx << "expected type: " << C_to_string[c] << std::endl;
                sx << "but got:" << std::endl;
                sx << "a = " << boost::core::demangled_name(a.type()) << std::endl;
                sx << "b = " << boost::core::demangled_name(b.type()) << std::endl;
                throw std::runtime_error(sx.str());
            }

            throw std::runtime_error("Illegal type provided");
        }
    }
}