#include "strategy/NoOpRemovalStrategy.h"
#include "step/logic/NoOpStep.h"

namespace gremlinxx {

    TraversalStrategy NoOpRemovalStrategy = {
        OPTIMIZATION,
        "NoOpRemovalStrategy",
        [](std::vector<std::shared_ptr<TraversalStep>>& steps){
            for(auto it = steps.begin(); it != steps.end(); ++it) {
                auto& step = *it;
                if(step->uid == NO_OP_STEP) {
                    it = steps.erase(it) - 1;
                }
            }
        }
    };

}