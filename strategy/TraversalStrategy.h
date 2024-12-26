#pragma once

#include <functional>
#include <vector>
#include <string>
#include <memory>

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"

namespace gremlinxx {
    enum TraversalStrategyType {
        DECORATION = 0,
        OPTIMIZATION = 1,
        PROVIDER = 2,
        FINALIZATON = 3,
        VERIFICATION = 4
    };

    extern std::unordered_map<TraversalStrategyType, std::string> strategy_type_names;

    /*
        Traversal Strategies operate on a vector of steps, mutating it as necessary.
    */
    struct TraversalStrategy {
        public:
            TraversalStrategyType type;
            std::string name;
            std::function<void(std::vector<std::shared_ptr<TraversalStep>>&)> apply;
            inline void operator()(std::vector<std::shared_ptr<TraversalStep>>& steps) { this->apply(steps); }
    };

}