#include "step/filter/IsStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"

#include "maelstrom/storage/comparison.h"
#include "maelstrom/algorithms/filter.h"
#include "maelstrom/algorithms/select.h"

namespace gremlinxx {

    IsStep::IsStep(P predicate)
    : TraversalStep(FILTER, IS_STEP) {
        this->predicate = predicate;
    }

    std::string IsStep::getInfo() { 
        std::string info = "IsStep{}";

        return info;
    }

    void IsStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        boost::any val = this->predicate.operand;
        auto cmp = this->predicate.comparison;

        traversers.advance([cmp, val](auto& data, auto& se, auto& paths){
            maelstrom::vector ix = maelstrom::filter(
                data,
                cmp,
                val
            );
            
            return std::make_pair(
                std::move(maelstrom::select(data, ix)),
                std::move(ix)
            );
        });
    }

}