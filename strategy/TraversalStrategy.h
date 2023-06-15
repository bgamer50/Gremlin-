#pragma once

#include <functional>
#include <vector>
#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"

namespace gremlinxx {

    /*
        Traversal Strategies operate on a vector of steps, mutating it as necessary.
    */
    typedef std::function<void(std::vector<TraversalStep*>&)> TraversalStrategy;

}