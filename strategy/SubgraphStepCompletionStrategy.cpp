#include "strategy/SubgraphStepCompletionStrategy.h"

#include "step/graph/SubgraphStep.h"
#include "step/graph/SubgraphExtractionStep.h"
#include "step/sideeffect/SelectStep.h"

namespace gremlinxx {

    TraversalStrategy SubgraphStepCompletionStrategy = {
        FINALIZATON,
        "SubgraphStepCompletionStrategy",
        [](std::vector<std::shared_ptr<TraversalStep>>& steps) {
        std::unordered_set<std::string> subgraph_names;
            for(auto it = steps.begin(); it != steps.end(); ++it) {
                TraversalStep* step = it->get();

                if(step->uid == SUBGRAPH_STEP) {
                    subgraph_names.insert(static_cast<SubgraphStep*>(step)->get_subgraph_name());
                }
                else if(step->uid == SELECT_STEP) {
                    auto f = subgraph_names.find(static_cast<SelectStep*>(step)->get_side_effect_label());
                    if(f != subgraph_names.end()) {
                        std::string name = *f;
                        it = steps.insert(it, std::shared_ptr<TraversalStep>(new SubgraphExtractionStep(name)));
                    }
                }
            }
        }
    };

}