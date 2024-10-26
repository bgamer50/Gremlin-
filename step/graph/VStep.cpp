#include "step/graph/VStep.h"
#include "util/gremlin_utils.h"

#include <iostream>
#include <sstream>

namespace gremlinxx {

    VStep::VStep(std::vector<std::any> eids)
    : TraversalStep(MAP, V_STEP) {
        this->element_ids = std::move(
            maelstrom::make_vector_from_anys(maelstrom::PINNED, eids)
        );
    }

    VStep::VStep(maelstrom::vector eids)
    : TraversalStep(MAP, V_STEP) {
        this->element_ids = std::move(eids);
    }

    std::string	VStep::getInfo() {
        std::stringstream sx;
        sx << "VStep(";
        sx << ((this->element_ids.empty()) ?  "" : "...");
        sx << ")";

        return sx.str();
    }

    void VStep::apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers) {
        throw std::runtime_error("Cannot call V() from an anonymous traversal!");
    }

}