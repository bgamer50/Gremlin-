#ifndef ID_STEP_H
#define ID_STEP_H

#include "TraversalStep.h"

#define ID_STEP 0x66

class IdStep : public TraversalStep {
    public:
        IdStep(): TraversalStep(MAP, ID_STEP) {}
};

#endif