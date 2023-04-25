#include "step/logic/NoOpStep.h"

NoOpStep::NoOpStep()
: TraversalStep(MAP, NO_OP_STEP) {}

std::string NoOpStep::getInfo() {
    return "NoOpStep()";
}

void NoOpStep::apply(GraphTraversal* traversal, TraverserSet& traversers){}