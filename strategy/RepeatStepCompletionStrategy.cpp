#include "strategy/RepeatStepCompletionStrategy.h"
#include "step/TraversalStep.h"
#include "step/controlflow/RepeatStep.h"
#include "step/controlflow/UntilStep.h"
#include "step/controlflow/EmitStep.h"
#include "step/controlflow/TimesStep.h"
#include "step/logic/NoOpStep.h"
#include <vector>

namespace gremlinxx {

    bool acquire_step(std::vector<std::shared_ptr<TraversalStep>>& steps, size_t idx, RepeatStep* repeatStep) {
        if(idx >= steps.size()) return false;

        auto uid = steps[idx]->uid;
        if(uid == UNTIL_STEP || uid == EMIT_STEP || uid == TIMES_STEP) {
            if(uid == UNTIL_STEP) {
                UntilStep* untilStep = static_cast<UntilStep*>(steps[idx].get());
                repeatStep->setUntilTraversal(untilStep->getTraversal());
            } else if(uid == EMIT_STEP) {
                EmitStep* emitStep = static_cast<EmitStep*>(steps[idx].get());
                repeatStep->setEmitTraversal(emitStep->getTraversal());
            } else {
                TimesStep* timesStep = static_cast<TimesStep*>(steps[idx].get());
                repeatStep->setTimes(timesStep->get_times());
            }
            // replace the step
            steps[idx] = std::shared_ptr<TraversalStep>(new NoOpStep());
            return true;
        }

        return false;
    }

    TraversalStrategy RepeatStepCompletionStrategy = {
        FINALIZATON,
        "RepeatStepCompletionStrategy",
        [](std::vector<std::shared_ptr<TraversalStep>>& steps) {
            for(size_t k = 0; k < steps.size(); ++k) {
                if(steps[k]->uid == REPEAT_STEP) {
                    if(acquire_step(steps, k-1, static_cast<RepeatStep*>(steps[k].get()))) acquire_step(steps, k-1, static_cast<RepeatStep*>(steps[k].get()));
                    if(acquire_step(steps, k+1, static_cast<RepeatStep*>(steps[k].get()))) acquire_step(steps, k+1, static_cast<RepeatStep*>(steps[k].get()));
                    // TODO might be an issue w/ stacked repeats, but why would you ever do that?
                }
            }
        }
    };

}