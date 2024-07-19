#include "step/filter/LimitStep.h"

namespace gremlinxx {

    LimitStep::LimitStep(uint64_t limit)
    : TraversalStep(FILTER, LIMIT_STEP) {
        this->limit = limit;
    }

    std::string LimitStep::getInfo() { return "LimitStep(" + std::to_string(limit) + ")"; }

    void LimitStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        if(limit > traversers.size()) {
            traversers.resize(limit);
        }
    }

}