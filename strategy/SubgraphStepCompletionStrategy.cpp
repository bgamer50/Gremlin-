#include "strategy/SubgraphStepCompletionStrategy.h"
#include "step/graph/SubgraphStep.h"
#include "step/graph/SubgraphExtractionStep.h"

#include <unordered_set>
#include <string>

namespace gremlinxx {

    TraversalStrategy SubgraphStepCompletionStrategy = {
        FINALIZATON,
        "SubgraphStepCompletionStrategy",
        [](std::vector<std::shared_ptr<TraversalStep>>& steps) {
            std::unordered_set<std::string> names;
            for(auto it = steps.begin(); it != steps.end(); ++it) {
                auto& step = *it;
                if(step->uid == SUBGRAPH_STEP) {
                    names.insert(
                        static_cast<SubgraphStep*>(step.get())->get_subgraph_name()
                    );
                }
            }

            steps.push_back(
                std::shared_ptr<TraversalStep>(
                    new SubgraphExtractionStep(std::move(names))
                )
            );
        }
    };

}