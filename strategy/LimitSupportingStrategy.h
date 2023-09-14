#pragma once

#include <vector>
#include <memory>

#include "step/TraversalStep.h"

namespace gremlinxx {
    void limit_supporting_strategy(std::vector<std::shared_ptr<TraversalStep>>& steps);
}
