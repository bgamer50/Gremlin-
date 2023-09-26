#include "step/sideeffect/SideEffectStep.h"

#include "maelstrom/algorithms/set.h"

namespace gremlinxx {

    void SideEffectStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        maelstrom::vector se_data(
            traversers.getCurrentMemType(),
            maelstrom::dtype_from_prim_type(maelstrom::prim_type_of(this->value)),
            traversers.size()
        );
        maelstrom::set(se_data, this->value);

        traversers.set_side_effects(
            this->label,
            std::move(se_data)
        );
    }

    std::string SideEffectStep::getInfo() {
        return "SideEffectStep{}";
    }

}