#include "traversal/Scope.h"

#include <stdexcept>

namespace gremlinxx {
        
    scope_group_t group_id_from_any(std::any a) {
        auto& id = a.type();
        if(id == typeid(int)) return static_cast<scope_group_t>(std::any_cast<int>(a));
        else if (id == typeid(long)) return static_cast<scope_group_t>(std::any_cast<long>(a));
        else if(id == typeid(unsigned int)) return static_cast<scope_group_t>(std::any_cast<unsigned int>(a));
        else if(id == typeid(unsigned long)) return static_cast<scope_group_t>(std::any_cast<unsigned long>(a));
        else if(id == typeid(char)) return static_cast<scope_group_t>(std::any_cast<char>(a));
        else if(id == typeid(unsigned char)) return static_cast<scope_group_t>(std::any_cast<unsigned char>(a));
        else if(id == typeid(short)) return static_cast<scope_group_t>(std::any_cast<short>(a));
        else if(id == typeid(unsigned short)) return static_cast<scope_group_t>(std::any_cast<unsigned short>(a));
        else if(id == typeid(float)) throw std::runtime_error("Float type not supported for scope groups");
        else if(id == typeid(double)) throw std::runtime_error("Double type not supported for scope groups");
        else if(id == typeid(std::string)) throw std::runtime_error("String type not supported for scope groups");
        else if(id == typeid(char*)) throw std::runtime_error("Char array type not supported for scope groups");
        else if(id == typeid(const char*)) throw std::runtime_error("Char array type not supported for scope groups");
        else throw std::runtime_error("Unknown type not supported for scope groups");
    }

    std::any any_from_group_id(scope_group_t group_id, const std::type_info& out_type) {
        if(out_type == typeid(int)) return std::any(static_cast<int>(group_id));
        else if (out_type == typeid(long)) return std::any(static_cast<long>(group_id));
        else if(out_type == typeid(unsigned int)) return std::any(static_cast<unsigned int>(group_id));
        else if(out_type == typeid(unsigned long)) return std::any(static_cast<unsigned long>(group_id));
        else if(out_type == typeid(char)) return std::any(static_cast<char>(group_id));
        else if(out_type == typeid(unsigned char)) return std::any(static_cast<unsigned char>(group_id));
        else if(out_type == typeid(short)) return std::any(static_cast<short>(group_id));
        else if(out_type == typeid(unsigned short)) return std::any(static_cast<unsigned short>(group_id));
        else if(out_type == typeid(float)) throw std::runtime_error("Float type not supported for scope groups");
        else if(out_type == typeid(double)) throw std::runtime_error("Double type not supported for scope groups");
        else if(out_type == typeid(std::string)) throw std::runtime_error("String type not supported for scope groups");
        else if(out_type == typeid(char*)) throw std::runtime_error("Char array type not supported for scope groups");
        else if(out_type == typeid(const char*)) throw std::runtime_error("Char array type not supported for scope groups");
        else throw std::runtime_error("Unknown type not supported for scope groups");
    }

}