#include "step/math/MinStep.h"

MinStep::MinStep(gremlinxx::comparison::C cmp_type)
: TraversalStep(true, MAP, MIN_STEP) {
    this->comparison_type = cmp_type;
}

void MinStep::apply_global(GraphTraversal* traversal, TraverserSet& traversers) {
    Traverser min_value = traversers.front();
    for(Traverser t : traversers) {
        min_value = this->min(t, min_value);
    }
    
    traversers.clear();
    traversers.push_back(min_value);
}

void MinStep::apply_local(GraphTraversal* traversal, TraverserSet& traversers) {
    std::unordered_map<scope_group_t, Traverser> min_values;
    std::for_each(traversers.begin(), traversers.end(), [this, &min_values](Traverser& t){
        scope_group_t group_id = boost::any_cast<scope_group_t>(t.get_side_effects()[*this->scope_context->side_effect_key]);
        if(min_values.find(group_id) == min_values.end()) min_values[group_id] = t;
        else {
            auto old_min = min_values[group_id];
            min_values[group_id] = this->min(t, old_min);
        }
    });
    
    traversers.clear();
    for(auto it = min_values.begin(); it != min_values.end(); ++it) traversers.push_back(it->second);
}

std::string MinStep::getInfo() { 
    std::string info = "MinStep{}";

    return info;
}

void MinStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    if(!traversers.empty()) {
        if(!scope_context || scope_context->scope == global) apply_global(traversal, traversers);
        else apply_local(traversal, traversers);
    }
}