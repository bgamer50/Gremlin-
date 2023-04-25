#include "step/controlflow/TimesStep.h"

TimesStep::TimesStep(size_t times)
: TraversalStep(MODULATOR, TIMES_STEP) {
    this->times = times;
}