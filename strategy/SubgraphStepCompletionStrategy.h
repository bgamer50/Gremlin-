#pragma once

#include "step/TraversalStep.h"
#include <vector>

namespace gremlinxx {
    void subgraph_step_completion_strategy(std::vector<TraversalStep*>& steps);
}
