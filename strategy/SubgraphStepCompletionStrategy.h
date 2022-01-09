#ifndef SUBGRAPH_STEP_COMPLETION_STRATEGY_H
#define SUBGRAPH_STEP_COMPLETION_STRATEGY_H

#include "step/graph/SubgraphStep.h"
#include "step/graph/SubgraphExtractionStep.h"

void subgraph_step_completion_strategy(std::vector<TraversalStep*>& steps) {
    std::unordered_set<std::string> subgraph_names;
    for(auto it = steps.begin(); it != steps.end(); ++it) {
        TraversalStep* step = *it;

        if(step->uid == SUBGRAPH_STEP) {
            subgraph_names.insert(static_cast<SubgraphStep*>(step)->get_subgraph_name());
        }
        else if(step->uid == SELECT_STEP) {
            auto f = subgraph_names.find(static_cast<SelectStep*>(step)->get_side_effect_label());
            if(f != subgraph_names.end()) {
                std::string name = *f;
                it = steps.insert(it, new SubgraphExtractionStep(name));
            }
        }
    }
}

#endif