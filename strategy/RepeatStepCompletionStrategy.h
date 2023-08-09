#pragma once

#include "step/TraversalStep.h"
#include <vector>
#include <memory>

namespace gremlinxx {

    void repeat_step_completion_strategy(std::vector<std::shared_ptr<TraversalStep>>& steps);
    
}

