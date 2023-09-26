#include "step/controlflow/LoopsStep.h"
#include "step/controlflow/RepeatStep.h"
#include "maelstrom/algorithms/set.h"

namespace gremlinxx {

    LoopsStep::LoopsStep()
    : TraversalStep(MAP, LOOPS_STEP) {}

    void LoopsStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        size_t loops = std::any_cast<size_t>(
            traversal->getTraversalProperty(LOOPS_TRAVERSAL_PROPERTY)
        );

        traversers.advance([loops](maelstrom::vector& traverser_data, std::unordered_map<std::string, maelstrom::vector>& side_effects, gremlinxx::traversal::PathInfo& path_info){
            maelstrom::vector new_traverser_data(
                traverser_data.get_mem_type(),
                maelstrom::uint64,
                traverser_data.size()
            );

            maelstrom::set(new_traverser_data, static_cast<size_t>(loops));

            return std::make_pair(
                new_traverser_data,
                maelstrom::vector()
            );
        });
    }

}