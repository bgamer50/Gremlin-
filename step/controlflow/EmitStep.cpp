#include "step/controlflow/EmitStep.h"

namespace gremlinxx {
 
    EmitStep::EmitStep(GraphTraversal traversal)
    : TraversalStep(MODULATOR, EMIT_STEP) {
        this->traversal = traversal;            
    }

    GraphTraversal EmitStep::getTraversal() { return this->traversal; }

    std::string EmitStep::getInfo() {
        return "EmitStep{traversal}";
    }

}