#include "strategy/RepeatStepCompletionStrategy.h"
#include "step/TraversalStep.h"
#include "step/controlflow/RepeatStep.h"
#include "step/controlflow/UntilStep.h"
#include "step/controlflow/EmitStep.h"
#include "step/controlflow/TimesStep.h"
#include "step/logic/NoOpStep.h"
#include <vector>

namespace gremlinxx {

    bool acquire_step(std::vector<TraversalStep*>& steps, size_t idx, RepeatStep* repeatStep) {
        if(idx >= steps.size()) return false;

        auto uid = steps[idx]->uid;
        if(uid == UNTIL_STEP || uid == EMIT_STEP || uid == TIMES_STEP) {
            if(uid == UNTIL_STEP) {
                UntilStep* untilStep = static_cast<UntilStep*>(steps[idx]);
                repeatStep->setUntilTraversal(untilStep->getTraversal());
            } else if(uid == EMIT_STEP) {
                EmitStep* emitStep = static_cast<EmitStep*>(steps[idx]);
                repeatStep->setEmitTraversal(emitStep->getTraversal());
            } else {
                TimesStep* timesStep = static_cast<TimesStep*>(steps[idx]);
                repeatStep->setTimes(timesStep->get_times());
            }
            // delete the step
            delete steps[idx];
            steps[idx] = static_cast<TraversalStep*>(new NoOpStep());
            return true;
        }

        return false;
    }

    void repeat_step_completion_strategy(std::vector<TraversalStep*>& steps) {
        for(size_t k = 0; k < steps.size(); ++k) {
            if(steps[k]->uid == REPEAT_STEP) {
                if(acquire_step(steps, k-1, static_cast<RepeatStep*>(steps[k]))) acquire_step(steps, k-1, static_cast<RepeatStep*>(steps[k]));
                if(acquire_step(steps, k+1, static_cast<RepeatStep*>(steps[k]))) acquire_step(steps, k+1, static_cast<RepeatStep*>(steps[k]));
                // TODO might be an issue w/ stacked repeats, but why would you ever do that?
            }
        }
    }

}