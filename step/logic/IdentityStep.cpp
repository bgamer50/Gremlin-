#include "step/logic/IdentityStep.h"

IdentityStep::IdentityStep()
: TraversalStep(MAP, IDENTITY_STEP) {}

std::string IdentityStep::getInfo() { return "IdentityStep{}"; }

void IdentityStep::apply(GraphTraversal* traversal, TraverserSet& traversers){}
