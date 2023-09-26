#pragma once

#include "step/TraversalStep.h"
#include <vector>
#include <memory>

namespace gremlinxx {

    void by_modulating_strategy(std::vector<std::shared_ptr<TraversalStep>>& steps);

}