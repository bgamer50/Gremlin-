#pragma once

#define UNTIL_STEP 0x43

#include "step/TraversalStep.h"
#include "traversal/GraphTraversal.h"

class UntilStep: public TraversalStep {
    private:
        GraphTraversal* traversal;

    public:
        UntilStep(GraphTraversal* traversal);

        inline GraphTraversal* getTraversal() { return this->traversal; }
};
