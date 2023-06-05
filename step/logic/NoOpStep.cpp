#include "step/logic/NoOpStep.h"

namespace gremlinxx {

    NoOpStep::NoOpStep()
    : TraversalStep(MAP, NO_OP_STEP) {}

    std::string NoOpStep::getInfo() {
        return "NoOpStep()";
    }

    void NoOpStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers){}

}