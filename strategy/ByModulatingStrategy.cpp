#include "strategy/ByModulatingStrategy.h"
#include "step/TraversalStep.h"
#include "step/modulate/ByModulating.h"
#include "step/modulate/ByStep.h"
#include "step/logic/NoOpStep.h"

namespace gremlinxx {

    TraversalStrategy ByModulatingStrategy = {
        FINALIZATON,
        "ByModulatingStrategy",
        [](std::vector<std::shared_ptr<TraversalStep>>& steps){
            if(steps[0]->uid == BY_STEP) throw std::runtime_error("Cannot start a traversal with by()!");

            for(size_t k = 1; k < steps.size(); ++k) {
                if(steps[k]->uid == BY_STEP) {
                    dynamic_cast<ByModulating*>(steps[k-1].get())->modulate_by(static_cast<ByStep*>(steps[k].get())->get());
                    
                    // replace the step
                    steps[k] = std::shared_ptr<TraversalStep>(new NoOpStep());
                }
            }
        }
    };

}