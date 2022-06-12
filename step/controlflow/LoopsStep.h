#ifndef LOOPS_STEP_H
#define LOOPS_STEP_H

#define LOOPS_STEP 0x4c

#include "step/TraversalStep.h"
#include "step/controlflow/RepeatStep.h"

class LoopsStep: public TraversalStep {
    private:
        GraphTraversal* traversal;

    public:
        LoopsStep()
        : TraversalStep(MAP, LOOPS_STEP) {   }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers) {
            for(Traverser& trv : traversers) trv.replace_data(traversal->getTraversalProperty(LOOPS_TRAVERSAL_PROPERTY));
        }
};

#endif