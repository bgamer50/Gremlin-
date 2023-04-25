#include "step/controlflow/LoopsStep.h"
#include "step/controlflow/RepeatStep.h"

LoopsStep::LoopsStep()
: TraversalStep(MAP, LOOPS_STEP) {}

void LoopsStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    for(Traverser& trv : traversers) trv.replace_data(traversal->getTraversalProperty(LOOPS_TRAVERSAL_PROPERTY));
}