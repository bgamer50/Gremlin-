#include "step/controlflow/UntilStep.h"

UntilStep::UntilStep(GraphTraversal* traversal)
: TraversalStep(MODULATOR, UNTIL_STEP) {
    this->traversal = traversal;            
}