#ifndef VALUEMAP_STEP_COMPLETION_STRATEGY_H
#define VALUEMAP_STEP_COMPLETION_STRATEGY_H

#include "step/TraversalStep.h"
#include "step/property/ValueMapStep.h"
#include "step/modulate/ByStep.h"
#include <vector>

void valuemap_step_completion_strategy(std::vector<TraversalStep*>& steps) {
    for(size_t k = 0; k < steps.size() - 1; ++k) {
        if(steps[k]->uid == VALUEMAP_STEP && steps[k+1]->uid == BY_STEP) {
            ValueMapStep* valuemap_step = dynamic_cast<ValueMapStep*>(steps[k]);
            ByStep* by_step = dynamic_cast<ByStep*>(steps[k+1]);

            valuemap_step->set_by_traversal(by_step->getTraversal());
            steps.erase(steps.begin() + k + 1);
        }
    }
}

#endif