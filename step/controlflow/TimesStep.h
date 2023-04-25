#pragma once

#define TIMES_STEP 0x4b

#include "step/TraversalStep.h"

class TimesStep: public TraversalStep {
    private:
        size_t times;

    public:
        TimesStep(size_t times);

        inline size_t get_times() { return this->times; }
};
