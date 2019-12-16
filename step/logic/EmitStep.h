#ifndef EMIT_STEP_H
#define EMIT_STEP_H

#define EMIT_STEP 0x44

#include "step/TraversalStep.h"

class EmitStep: public TraversalStep {
    private:
        GraphTraversal* traversal;

    public:
        EmitStep(GraphTraversal* traversal)
        : TraversalStep(MODULATOR, EMIT_STEP) {
            this->traversal = traversal;            
        }

        GraphTraversal* getTraversal() { return this->traversal; }
};

#endif