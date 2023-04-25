#include "traversal/Traverser.h"

Traverser::Traverser(boost::any t) {
    my_data = boost::any(t);
}

Traverser::Traverser(boost::any t, std::map<std::string, boost::any>& new_side_effects) {
    my_data = boost::any(t);
    this->side_effects = new_side_effects;
}

Traverser::Traverser() : Traverser(boost::any()){}

boost::any Traverser::get() {
    return my_data;
}

Traverser Traverser::replace_data(boost::any t) {
    my_data = t;
    return *this;
}

std::map<std::string, boost::any>& Traverser::get_side_effects() {
    return this->side_effects;
}