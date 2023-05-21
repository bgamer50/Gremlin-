#include "step/graph/IdStep.h"
#include "traversal/GraphTraversal.h"

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
                return std::make_pair(
                    std::move(maelstrom::as_primitive_vector(traverser_data, false)),
                    std::move(maelstrom::vector())
                );

            } else {
                throw std::runtime_error("Only vertices are currently supported by Id Step!");
            }
        });
    }

}