#include "step/controlflow/LoopsStep.h"
#include "step/controlflow/RepeatStep.h"

LoopsStep::LoopsStep()
: TraversalStep(MAP, LOOPS_STEP) {}

void LoopsStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet* traversers) {
    std::vector<boost::any> l(traversers->size(), traversal->getTraversalProperty(LOOPS_TRAVERSAL_PROPERTY));
    traversers->advance(l);
}