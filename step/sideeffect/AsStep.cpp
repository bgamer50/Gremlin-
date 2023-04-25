#include "step/sideeffect/AsStep.h"
#include "traversal/GraphTraversal.h"

AsStep::AsStep(std::string se_label)
: TraversalStep(SIDE_EFFECT, AS_STEP) {
    this->sideEffectLabel = se_label;
}

std::string AsStep::getInfo() { return "AsStep{" + sideEffectLabel + "}"; }

void AsStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    for(Traverser& trv : traversers) {
        trv.get_side_effects()[sideEffectLabel] = trv.get();
    }
}
