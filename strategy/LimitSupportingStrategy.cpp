#include "strategy/LimitSupportingStrategy.h"
#include "step/filter/LimitStep.h"
#include "step/filter/LimitSupportingStep.h"
#include "step/logic/NoOpStep.h"

namespace gremlinxx {

    TraversalStrategy LimitSupportingStrategy = {
        OPTIMIZATION,
        "LimitStepStrategy",
        [](std::vector<std::shared_ptr<TraversalStep>>& steps) {
            for(size_t k = 1; k < steps.size(); ++k) {
                if(steps[k]->uid == LIMIT_STEP) {
                    LimitStep* ls = static_cast<LimitStep*>(steps[k].get());
                    LimitSupportingStep* lss = dynamic_cast<LimitSupportingStep*>(steps[k-1].get());
                    if(lss != nullptr) {
                        lss->set_limit(ls->get_limit());
                        steps[k] = std::move(
                            std::shared_ptr<TraversalStep>(new NoOpStep())
                        );
                    }
                }
            }
        }
    };

}