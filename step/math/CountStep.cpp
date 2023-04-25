#include "step/math/CountStep.h"
#include "traversal/GraphTraversal.h"

CountStep::CountStep()
: TraversalStep(true, MAP, COUNT_STEP) {}

std::string CountStep::getInfo() {
    return std::string("CountStep{}");
}

void CountStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    size_t size = traversers.size();
    traversers.clear();
    traversers.push_back(Traverser(size));
}
