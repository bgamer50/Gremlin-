#include "step/controlflow/UnionStep.h"
#include "traversal/Traverser.h"

std::string UnionStep::getInfo() { 
    std::string info = "UnionStep{}";

    return info;
}

UnionStep::UnionStep(std::vector<GraphTraversal*>& traversals)
: TraversalStep(MAP, UNION_STEP) {
    for(auto it = traversals.begin(); it != traversals.end(); ++it) this->traversals.push_back(*it);
}

std::vector<GraphTraversal*>& UnionStep::get_traversals() {
    return this->traversals;
}

void UnionStep::apply(GraphTraversal* parent_traversal, TraverserSet& traversers) {
    size_t num_traversers = traversers.size();
    TraverserSet new_traversers;

    for(auto it = this->traversals.begin(); it != this->traversals.end(); ++it) {
        GraphTraversal* current_union_traversal = *it;

        GraphTraversal executing_traversal(parent_traversal->getTraversalSource(), current_union_traversal);
        TraverserSet temp_traversers(traversers.begin(), traversers.end());
        executing_traversal.setInitialTraversers(temp_traversers);
        executing_traversal.iterate();
        
        auto output_traversers = executing_traversal.getTraversers();
        new_traversers.insert(new_traversers.end(), output_traversers.begin(), output_traversers.end());
    }

    traversers.swap(new_traversers);
}