#ifndef SCOPE_H
#define SCOPE_H

#include <boost/any.hpp>
#include <optional>
#include <string>
#include <inttypes.h>

enum Scope {local, global};

typedef struct ScopeContext {
    Scope scope;
    std::optional<std::string> side_effect_key;
} ScopeContext;

typedef int64_t scope_group_t;

scope_group_t group_id_from_any(boost::any a) {
    auto& id = a.type();
    if(id == typeid(int)) return static_cast<scope_group_t>(boost::any_cast<int>(a));
    else if (id == typeid(long)) return static_cast<scope_group_t>(boost::any_cast<long>(a));
    else if(id == typeid(unsigned int)) return static_cast<scope_group_t>(boost::any_cast<unsigned int>(a));
    else if(id == typeid(unsigned long)) return static_cast<scope_group_t>(boost::any_cast<unsigned long>(a));
    else if(id == typeid(char)) return static_cast<scope_group_t>(boost::any_cast<char>(a));
    else if(id == typeid(unsigned char)) return static_cast<scope_group_t>(boost::any_cast<unsigned char>(a));
    else if(id == typeid(short)) return static_cast<scope_group_t>(boost::any_cast<short>(a));
    else if(id == typeid(unsigned short)) return static_cast<scope_group_t>(boost::any_cast<unsigned short>(a));
    else if(id == typeid(float)) throw std::runtime_error("Float type not supported for scope groups");
    else if(id == typeid(double)) throw std::runtime_error("Double type not supported for scope groups");
    else if(id == typeid(std::string)) throw std::runtime_error("String type not supported for scope groups");
    else if(id == typeid(char*)) throw std::runtime_error("Char array type not supported for scope groups");
    else if(id == typeid(const char*)) throw std::runtime_error("Char array type not supported for scope groups");
    else throw std::runtime_error("Unknown type not supported for scope groups");
}

boost::any any_from_group_id(scope_group_t group_id, const std::type_info& out_type) {
    if(out_type == typeid(int)) return boost::any(static_cast<int>(group_id));
    else if (out_type == typeid(long)) return boost::any(static_cast<long>(group_id));
    else if(out_type == typeid(unsigned int)) return boost::any(static_cast<unsigned int>(group_id));
    else if(out_type == typeid(unsigned long)) return boost::any(static_cast<unsigned long>(group_id));
    else if(out_type == typeid(char)) return boost::any(static_cast<char>(group_id));
    else if(out_type == typeid(unsigned char)) return boost::any(static_cast<unsigned char>(group_id));
    else if(out_type == typeid(short)) return boost::any(static_cast<short>(group_id));
    else if(out_type == typeid(unsigned short)) return boost::any(static_cast<unsigned short>(group_id));
    else if(out_type == typeid(float)) throw std::runtime_error("Float type not supported for scope groups");
    else if(out_type == typeid(double)) throw std::runtime_error("Double type not supported for scope groups");
    else if(out_type == typeid(std::string)) throw std::runtime_error("String type not supported for scope groups");
    else if(out_type == typeid(char*)) throw std::runtime_error("Char array type not supported for scope groups");
    else if(out_type == typeid(const char*)) throw std::runtime_error("Char array type not supported for scope groups");
    else throw std::runtime_error("Unknown type not supported for scope groups");
}

#endif