#pragma once

#define EMIT_STEP 0x44

#include "step/TraversalStep.h"

class EmitStep: public TraversalStep {
    private:
        GraphTraversal* traversal;

    public:
        EmitStep(GraphTraversal* traversal);

        inline GraphTraversal* getTraversal() { return this->traversal; }
};
