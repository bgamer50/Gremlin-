#include "step/logic/DedupStep.h"
#include "traversal/GraphTraversalSource.h"
#include "traversal/GraphTraversal.h"
#include "maelstrom/algorithms/unique.h"
#include "maelstrom/algorithms/sort.h"
#include "maelstrom/algorithms/select.h"

namespace gremlinxx {

    // This is a barrier step
    DedupStep::DedupStep()
    : TraversalStep(true, FILTER, DEDUP_STEP) {}

    void DedupStep::modulate_by(boost::any arg) { 
        this->dedup_by_key = boost::any_cast<std::string>(arg);
    }

    void DedupStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        traversers.advance([](auto& traverser_data, auto& traverser_se, auto& traverser_path_info){
            maelstrom::vector sorted_data(traverser_data);
            maelstrom::vector sorted_indices = maelstrom::sort(sorted_data);
            
            maelstrom::vector unique_indices = maelstrom::unique(sorted_data);
            sorted_data.clear();
            unique_indices = maelstrom::select(sorted_indices, unique_indices);
            sorted_indices.clear();

            return std::make_pair(
                std::move(maelstrom::select(traverser_data, unique_indices)),
                std::move(unique_indices)
            );
        });
    }

    std::string DedupStep::getInfo() {
        return "DedupStep(" + this->dedup_by_key.value_or("") + ")";
    }

}