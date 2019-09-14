#ifndef COUNT_STEP_H
#define COUNT_STEP_H

#define COUNT_STEP 0x61

#include "TraversalStep.h"
#include <functional>

class CountStep : public TraversalStep {
    public:
        CountStep()
        : TraversalStep(MAP, COUNT_STEP) {
            // empty constructor
        }
};

#endif