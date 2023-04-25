/*
    This header contains helper methods for comparisons of various property types.
    It is often used in conjunction with the min() and max() steps.
*/

#pragma once

#include <cstdint>
#include <boost/any.hpp>
#include <boost/core/typeinfo.hpp>
#include <sstream>
#include <string>
#include <vector>

class Vertex;

namespace gremlinxx {
    namespace comparison {

        enum C {UINT64=0, UINT32=1, INT64=2, INT32=3, FLOAT64=4, FLOAT32=5, UINT8=6, INT8=7, STRING=8, VERTEX=9};
        extern std::vector<std::string> C_to_string;
        extern std::vector<size_t> C_size;

        // Conversion from type to C type id
        template<class T>
        C C_TYPEID();


        // Templated function and declarations for calling less()
        template<typename T> 
        bool __call_less(boost::any a, boost::any b);

        // Calls the appropriate version of std::less corresponding to the C dtype provided
        // If either object does not match the expected C dtype, an error is thrown.
        // This method will not cast to the correct dtypes, it is up to the caller to ensure
        // the dtypes match.
        bool C_LESS(C c, boost::any a, boost::any b);

        // Get the corresponding C data type id from a boost::any
        C from_any(boost::any& a);
    }
}