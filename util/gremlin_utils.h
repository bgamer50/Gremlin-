#pragma once

#include <any>
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

typedef std::unordered_map<std::string, std::any> valuemap_t;
typedef std::vector<std::any> anyvec_t;

inline std::string string_any(std::any a) {
    auto& id = a.type();
    if(id == typeid(int)) return std::to_string(std::any_cast<int>(a));
    else if (id == typeid(long)) return std::to_string(std::any_cast<long>(a));
    else if(id == typeid(unsigned int)) return std::to_string(std::any_cast<unsigned int>(a));
    else if(id == typeid(unsigned long)) return std::to_string(std::any_cast<unsigned long>(a));
    else if(id == typeid(float)) return std::to_string(std::any_cast<float>(a));
    else if(id == typeid(double)) return std::to_string(std::any_cast<double>(a));
    else if(id == typeid(std::string)) return std::any_cast<std::string>(a);
    //else if(id == typeid(unsigned char*)) return std::string(std::any_cast<unsigned char*>(a));
    else if(id == typeid(char*)) return std::string(std::any_cast<char*>(a));
    else if(id == typeid(const char*)) return std::string(std::any_cast<const char*>(a));
    else return std::string("?");
}

inline void print_any(std::any a) {
    std::cout << string_any(a) << std::endl;
}

inline void print_valuemap(std::any vm) {
    std::cout << "{";
    for(auto p : std::any_cast<valuemap_t>(vm)) {
        std::cout << p.first << ": ";
        if(typeid(anyvec_t) == p.second.type()) {
            anyvec_t av = std::any_cast<anyvec_t>(p.second);
            std::cout << "[";
            for(std::any& b : av) {
                print_any(b);
                std::cout << ",";
            }
            std::cout << "]";
        } else {
            print_any(p.second);
        }
        std::cout << "; ";
    }
    std::cout << "}" << std::endl;
}
