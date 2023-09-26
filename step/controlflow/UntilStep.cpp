#include "step/controlflow/UntilStep.h"

namespace gremlinxx {

    UntilStep::UntilStep(GraphTraversal traversal)
    : TraversalStep(MODULATOR, UNTIL_STEP) {
        this->traversal = traversal;            
    }

}