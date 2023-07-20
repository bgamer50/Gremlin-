#include "traversal/Traverser.h"

namespace gremlinxx {
        
    Traverser::Traverser(std::any t) {
        my_data = std::any(t);
    }

    Traverser::Traverser(std::any t, std::unordered_map<std::string, std::any>& new_side_effects) {
        my_data = std::any(t);
        this->side_effects = new_side_effects;
    }

    Traverser::Traverser() : Traverser(std::any()){}

    std::any Traverser::get() {
        return my_data;
    }

    void Traverser::replace_data(std::any t) {
        my_data = t;
    }

    std::unordered_map<std::string, std::any>& Traverser::access_side_effects() {
        return this->side_effects;
    }

    std::vector<std::any>& Traverser::access_path() {
        return this->path;
    }

}