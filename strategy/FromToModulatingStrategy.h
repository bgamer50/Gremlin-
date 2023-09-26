#pragma once
#include <vector>
#include <memory>

#include "step/TraversalStep.h"

namespace gremlinxx {
    void from_to_modulating_strategy(std::vector<std::shared_ptr<TraversalStep>>& steps);
}
