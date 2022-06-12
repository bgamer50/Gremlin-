#ifndef COUNT_STEP_H
#define COUNT_STEP_H

#define COUNT_STEP 0x61

#include "step/TraversalStep.h"
#include <functional>

class CountStep : public TraversalStep {
    public:
        CountStep()
        : TraversalStep(true, MAP, COUNT_STEP) {
            // empty constructor
        }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers) {
            size_t size = traversers.size();
			traversers.clear();
			traversers.push_back(Traverser(size));
        }
};

#endif