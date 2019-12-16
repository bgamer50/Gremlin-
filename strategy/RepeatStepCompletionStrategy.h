#ifndef REPEAT_STEP_COMPLETION_STRATEGY_H
#define REPEAT_STEP_COMPLETION_STRATEGY_H

#include "step/TraversalStep.h"
#include "step/logic/RepeatStep.h"
#include "step/logic/UntilStep.h"
#include "step/logic/EmitStep.h"
#include <vector>

bool acquire_step(std::vector<TraversalStep*>& steps, size_t idx, RepeatStep* repeatStep) {
    if(idx < 0 || idx >= steps.size()) return false;

    auto uid = steps[idx]->uid;
    if(uid == UNTIL_STEP || uid == EMIT_STEP) {
        if(uid == UNTIL_STEP) {
            UntilStep* untilStep = reinterpret_cast<UntilStep*>(steps[idx]);
            repeatStep->setUntilTraversal(untilStep->getTraversal());
        } else {
            EmitStep* emitStep = reinterpret_cast<EmitStep*>(steps[idx]);
            repeatStep->setEmitTraversal(emitStep->getTraversal());
        }
        // delete the step
        steps.erase(steps.begin() + idx);
        return true;
    }

    return false;
}

void repeat_step_completion_strategy(std::vector<TraversalStep*>& steps) {
    for(size_t k = 0; k < steps.size(); ++k) {
        if(steps[k]->uid == REPEAT_STEP) {
            if(acquire_step(steps, k-1, reinterpret_cast<RepeatStep*>(steps[k]))) acquire_step(steps, k-1, reinterpret_cast<RepeatStep*>(steps[k]));
            if(acquire_step(steps, k+1, reinterpret_cast<RepeatStep*>(steps[k]))) acquire_step(steps, k+1, reinterpret_cast<RepeatStep*>(steps[k]));
            // TODO might be an issue w/ stacked repeats, but why would you ever do that?
        }
    }
}

#endif