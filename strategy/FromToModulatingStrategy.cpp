#include "strategy/FromToModulatingStrategy.h"
#include "step/TraversalStep.h"
#include "step/modulate/FromStep.h"
#include "step/modulate/ToStep.h"
#include "step/logic/NoOpStep.h"
#include "step/modulate/FromToModulating.h"
#include <vector>

namespace gremlinxx {

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
                auto base_step = dynamic_cast<FromToModulating*>(steps[i]);
                auto from_modulator = static_cast<FromStep*>(currentStep);
                GraphTraversal trv(from_modulator->get_traversal());
                base_step->modulate_from(std::move(trv));

                delete steps[k];
                steps[k] = new NoOpStep();
            } else if(currentStep->uid == TO_STEP) {
                int i = k-1; while(steps[i]->uid == NO_OP_STEP) --i;
                auto base_step = dynamic_cast<FromToModulating*>(steps[i]);
                auto to_modulator = static_cast<ToStep*>(currentStep);
                GraphTraversal trv(to_modulator->get_traversal());
                base_step->modulate_to(std::move(trv));
                
                delete steps[k];
                steps[k] = new NoOpStep();
            }
        }
    }


}