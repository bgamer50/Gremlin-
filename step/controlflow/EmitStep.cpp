#include "step/controlflow/EmitStep.h"

EmitStep::EmitStep(GraphTraversal* traversal)
: TraversalStep(MODULATOR, EMIT_STEP) {
    this->traversal = traversal;            
}