#ifndef BY_MODULATING_STRATEGY_H
#define BY_MODULATING_STRATEGY_H

#include "step/TraversalStep.h"
#include "step/property/ValueMapStep.h"
#include "step/modulate/ByStep.h"
#include "step/logic/NoOpStep.h"
#include <vector>

void by_modulating_strategy(std::vector<TraversalStep*>& steps) {
    if(steps[0]->uid == BY_STEP) throw std::runtime_error("Cannot start a traversal with by()!");

    for(size_t k = 1; k < steps.size(); ++k) {
        if(steps[k]->uid == BY_STEP) {
            dynamic_cast<ByModulating*>(steps[k-1])->modulate_by(static_cast<ByStep*>(steps[k])->get());
            delete steps[k];
            steps[k] = new NoOpStep();
        }
    }
}

#endif