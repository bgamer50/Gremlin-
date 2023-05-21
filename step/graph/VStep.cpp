#include "step/graph/VStep.h"
#include "util/gremlin_utils.h"

#include <sstream>

namespace gremlinxx {

    VStep::VStep(std::vector<boost::any> eids)
    : TraversalStep(MAP, V_STEP) {
        this->element_ids = eids;
    }

    std::string	VStep::getInfo() {
        std::stringstream sx;
        sx << "VStep(";
        for(size_t k = 0; (k < 6) && (k < this->element_ids.size() - 1); ++k) {
            sx << string_any(this->element_ids[k]) << ", ";
        }
        sx << "...";
        sx << string_any(this->element_ids[this->element_ids.size() - 1]) << ")";
    }

    void VStep::apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers) {
        throw std::runtime_error("Unsupported operation!");
    }

}