#include "step/logic/OrderStep.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"

#include "maelstrom/algorithms/sort.h"
#include "maelstrom/algorithms/select.h"

namespace gremlinxx {

    // This is a barrier step
    OrderStep::OrderStep()
    : TraversalStep(true, MAP, ORDER_STEP) {}


    void OrderStep::modulate_by(std::any arg) { this->order_traversal = std::any_cast<GraphTraversal*>(arg); }

    std::string OrderStep::getInfo() {
        if(this->order_traversal == nullptr) return "OrderStep()";
        else return "OrderStep(" + this->order_traversal->explain() + ")";
    }

    void OrderStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        traversers.advance([](auto& traverser_data, auto& traverser_se, auto& traverser_paths){
            maelstrom::vector sorted_data(traverser_data);
            auto perm = maelstrom::sort(sorted_data);
            
            return std::make_pair(
                std::move(sorted_data),
                std::move(perm)
            );
        });

        // Erase 1 level of paths (this is efficient chopping from the right like we're doing here)
        traversers.trim_paths(0, traversers.getPathLength() - 1);
        
    }

}