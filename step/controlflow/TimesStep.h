#ifndef TIMES_STEP_H
#define TIMES_STEP_H

#define TIMES_STEP 0x4b

#include "step/TraversalStep.h"

class TimesStep: public TraversalStep {
    private:
        size_t times;

    public:
        TimesStep(size_t times)
        : TraversalStep(MODULATOR, TIMES_STEP) {
            this->times = times;
        }

        size_t get_times() { return this->times; }
};

#endif