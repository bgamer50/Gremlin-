#include "step/sideeffect/AsStep.h"
#include "traversal/GraphTraversal.h"

namespace gremlinxx {
        
    AsStep::AsStep(std::string se_label)
    : TraversalStep(SIDE_EFFECT, AS_STEP) {
        this->sideEffectLabel = se_label;
    }

    std::string AsStep::getInfo() { return "AsStep{" + sideEffectLabel + "}"; }

    void AsStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        traversers.set_side_effects(
            this->sideEffectLabel,
            std::move(traversers.getTraverserData())
        );
    }


}