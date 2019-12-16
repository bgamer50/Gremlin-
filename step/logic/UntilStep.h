#ifndef UNTIL_STEP_H
#define UNTIL_STEP_H

#define UNTIL_STEP 0x43

#include "step/TraversalStep.h"

class UntilStep: public TraversalStep {
    private:
        GraphTraversal* traversal;

    public:
        UntilStep(GraphTraversal* traversal)
        : TraversalStep(MODULATOR, UNTIL_STEP) {
            this->traversal = traversal;            
        }

        GraphTraversal* getTraversal() { return this->traversal; }
};

#endif