#ifndef IDENTITY_STEP_H
#define IDENTITY_STEP_H

#define IDENTITY_STEP 0x01
#include "TraversalStep.h"

class IdentityStep: public TraversalStep {
    public:
        IdentityStep()
        : TraversalStep(MAP, IDENTITY_STEP) {}
};

#endif