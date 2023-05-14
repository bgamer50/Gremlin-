#include "traversal/Traverser.h"

Traverser::Traverser(boost::any t) {
    my_data = boost::any(t);
}

Traverser::Traverser(boost::any t, std::unordered_map<std::string, boost::any>& new_side_effects) {
    my_data = boost::any(t);
    this->side_effects = new_side_effects;
}

Traverser::Traverser() : Traverser(boost::any()){}

boost::any Traverser::get() {
    return my_data;
}

void Traverser::replace_data(boost::any t) {
    my_data = t;
}

std::unordered_map<std::string, boost::any>& Traverser::access_side_effects() {
    return this->side_effects;
}

std::vector<boost::any>& Traverser::access_path() {
    return this->path;
}