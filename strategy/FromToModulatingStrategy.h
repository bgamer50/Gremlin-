#ifndef FROM_TO_MODULATING_STRATEGY
#define FROM_TO_MODULATING_STRATEGY

#include <vector>

void from_to_modulating_strategy(std::vector<TraversalStep*>& steps);

#include "traversal/GraphTraversal.h"
#include "step/modulate/FromStep.h"
#include "step/modulate/ToStep.h"
#include "step/logic/NoOpStep.h"
#include "step/modulate/FromToModulating.h"

/*
    Core strategy method
*/
void from_to_modulating_strategy(std::vector<TraversalStep*>& steps) {
    if(steps[0]->uid == FROM_STEP || steps[0]->uid == TO_STEP) {
        throw std::runtime_error("Cannot start a traversal with from() or to()!");
    }
    for(int k = 1; k < steps.size(); k++) {
		TraversalStep* currentStep = steps[k];
        if(currentStep->uid == FROM_STEP) {
            int i = k - 1; while(steps[i]->uid == NO_OP_STEP) --i;
            dynamic_cast<FromToModulating*>(steps[i])->modulate_from(static_cast<FromStep*>(currentStep)->get());
            delete steps[k];
            steps[k] = new NoOpStep();
        } else if(currentStep->uid == TO_STEP) {
            int i = k-1; while(steps[i]->uid == NO_OP_STEP) --i;
            dynamic_cast<FromToModulating*>(steps[i])->modulate_to(static_cast<ToStep*>(currentStep)->get());
            delete steps[k];
            steps[k] = new NoOpStep();
        }
	}
}

#endif