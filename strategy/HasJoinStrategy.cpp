#include "strategy/HasJoinStrategy.h"
#include "step/property/HasStep.h"

namespace gremlinxx {

    TraversalStrategy HasJoinStrategy = {
        OPTIMIZATION,
        "HasJoinStrategy",
        [](std::vector<std::shared_ptr<TraversalStep>>& steps){
            for(auto it = steps.begin(); it != steps.end(); ++it) {
                if((*it)->uid == HAS_STEP) {
                    HasStep* has_step = static_cast<HasStep*>(it->get());
                    while(it != steps.end() - 1 && (*(it+1))->uid == HAS_STEP) {
                        HasStep* next_has_step = static_cast<HasStep*>((it+1)->get());
                        has_step->join(next_has_step);

                        it = steps.erase(it+1) - 1;
                        if(it->get() != has_step) throw std::domain_error("Expected a Has Step");
                    }
                }
            }
        }
    };

}