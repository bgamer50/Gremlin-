#ifndef IDENTITY_STEP_H
#define IDENTITY_STEP_H

#define IDENTITY_STEP 0x01
#include "step/TraversalStep.h"
#include "Traverser.h"
#include "GraphTraversal.h"

class IdentityStep: public TraversalStep {
    public:
        IdentityStep()
        : TraversalStep(MAP, IDENTITY_STEP) {}

        virtual void apply(GraphTraversal* traversal, TraverserSet traversers){}
};

#endif