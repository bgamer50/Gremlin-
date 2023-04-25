#include "step/logic/FoldStep.h"

FoldStep::FoldStep()
: TraversalStep(MAP, FOLD_STEP) {}

std::string FoldStep::getInfo() {
    return std::string("FoldStep{}");
}

void FoldStep::apply(GraphTraversal* traversal, TraverserSet& traversers){
    TraverserSet new_traversers;

    size_t sz = traversers.size();
    std::vector<boost::any> vec(sz);
    for(size_t k = 0; k < sz; ++k) {
        vec[k] = traversers[k].get();
    }

    traversers.clear();
    traversers.push_back(Traverser(vec));
}