#include "strategy/RepeatUnrollStrategy.h"
#include "step/controlflow/RepeatStep.h"

namespace gremlinxx {

    TraversalStrategy RepeatUnrollStrategy = {
        OPTIMIZATION,
        "RepeatUnrollStrategy",
        [](std::vector<std::shared_ptr<TraversalStep>>& steps){
            for(auto it = steps.begin(); it != steps.end(); ++it) {
                auto& step = *it;
                if(step->uid == REPEAT_STEP) {
                    RepeatStep* rs = static_cast<RepeatStep*>(step.get());
                    if(!rs->hasEmitTraversal() && !rs->hasUntilTraversal() && rs->hasTimes()) {
                        size_t times = rs->getTimes();
                        auto new_steps = rs->getActionTraversal().getSteps();

                        for(size_t k = 0; k < times; ++k) {
                            it = steps.insert(it+1,  new_steps.begin(), new_steps.end());
                        }
                        it = steps.erase(it-times) - 1;
                    }
                }
            }
        }
    };

}