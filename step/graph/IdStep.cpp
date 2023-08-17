#include "step/graph/IdStep.h"
#include "traversal/GraphTraversal.h"
#include "structure/Graph.h"

#include "maelstrom/algorithms/arange.h"

namespace gremlinxx {

    IdStep::IdStep()
    : TraversalStep(MAP, ID_STEP) {}

    std::string IdStep::getInfo() {
        return "IdStep()";
    }

    void IdStep::apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers) {
        traversers.advance([trv](maelstrom::vector& traverser_data, std::unordered_map<std::string, maelstrom::vector>& traverser_side_effects, gremlinxx::traversal::PathInfo& traverser_paths){
            if(traverser_data.get_dtype() == trv->getGraph()->get_vertex_dtype()) {
                // In gremlin++, vertices in a traversal are represented by IDs, not pointers.
                // Therefore, this step only casts to the primitive type.
                // Also note that in gremlin++, vertex/edge ids have to be size_t, even though internally they are allowed to be arbitrary type

                return std::make_pair(
                    std::move(traverser_data.astype(maelstrom::uint64)),
                    std::move(maelstrom::arange(traverser_data.get_mem_type(), static_cast<size_t>(0), static_cast<size_t>(traverser_data.size())))
                );

            } else {
                throw std::runtime_error("Only vertices are currently supported by Id Step!");
            }
        });
    }

}