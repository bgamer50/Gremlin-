#include "step/filter/LimitStep.h"

LimitStep::LimitStep(uint64_t limit)
: TraversalStep(FILTER, LIMIT_STEP) {
    this->limit = limit;
}

std::string LimitStep::getInfo() { return "LimitStep(" + std::to_string(limit) + ")"; }

void LimitStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    if(traversers.size() > this->limit) traversers.resize(limit);
}