#include "traversal/Comparison.h"

namespace gremlinxx {
    namespace comparison {
        std::vector<std::string> C_to_string = {"UINT64", "UINT32", "INT64", "INT32", "FLOAT64", "FLOAT32", "UINT8", "INT8", "STRING", "VERTEX"};

        std::vector<size_t> C_size = {sizeof(uint64_t), sizeof(uint32_t), sizeof(int64_t), sizeof(int32_t), sizeof(double), sizeof(float), sizeof(uint8_t), sizeof(int8_t), sizeof(uint64_t), sizeof(Vertex*)};

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

        C from_any(boost::any& a) {
            const std::type_info& t = a.type();
			if(t == typeid(uint64_t)) {
                return C::UINT64;
            } else if(t == typeid(uint32_t)) {
                return C::UINT32;
            } else if(t == typeid(uint8_t)) {
                return C::UINT8;
            } else if(t == typeid(int64_t)) {
                return C::INT64;
            } else if(t == typeid(int32_t)) {
                return C::INT32;
            } else if(t == typeid(int8_t)) {
                return C::INT8;
            } else if(t == typeid(double)) {
                return C::FLOAT64;
            } else if(t == typeid(float)) {
                return C::FLOAT32;
            } else if(t == typeid(std::string)) {
                return C::STRING;
            } else if(t == typeid(Vertex*)) {
                return C::VERTEX;
            }

            std::stringstream sx;
            sx << "Illegal type " << boost::core::demangled_name(t) << " provided to from_any";
            throw std::runtime_error(sx.str());
        }
    }
}