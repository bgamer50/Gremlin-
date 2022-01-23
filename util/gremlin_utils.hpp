#ifndef GREMLIN_UTILS_H
#define GREMLIN_UTILS_H

#include <boost/any.hpp>
#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, boost::any> valuemap_t;
typedef std::vector<boost::any> anyvec_t;

std::string string_any(boost::any& a) {
    auto& id = a.type();
    if(id == typeid(int)) return std::to_string(boost::any_cast<int>(a));
    else if (id == typeid(long)) return std::to_string(boost::any_cast<long>(a));
    else if(id == typeid(unsigned int)) return std::to_string(boost::any_cast<unsigned int>(a));
    else if(id == typeid(unsigned long)) return std::to_string(boost::any_cast<unsigned long>(a));
    else if(id == typeid(float)) return std::to_string(boost::any_cast<float>(a));
    else if(id == typeid(double)) return std::to_string(boost::any_cast<double>(a));
    else if(id == typeid(std::string)) return boost::any_cast<std::string>(a);
    else if(id == typeid(unsigned char*)) return std::string(boost::any_cast<unsigned char*>(a));
    else if(id == typeid(char*)) return std::string(boost::any_cast<char*>(a));
    else if(id == typeid(const char*)) return std::string(boost::any_cast<const char*>(a));
    else std::cout << "?";
}

void print_any(boost::any& a) {
    std::cout << string_any(a) << std::endl;
}

void print_valuemap(boost::any vm) {
    std::cout << "{";
    for(auto p : boost::any_cast<valuemap_t>(vm)) {
        std::cout << p.first << ": ";
        if(typeid(anyvec_t) == p.second.type()) {
            anyvec_t av = boost::any_cast<anyvec_t>(p.second);
            std::cout << "[";
            for(boost::any& b : av) {
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

#endif