#ifndef TRAVERSAL_STRATEGY_H
#define TRAVERSAL_STRATEGY_H

#include <functional>
#include <vector>
#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"

/*
    Traversal Strategies operate on a vector of steps, mutating it as necessary.
*/
typedef std::function<void(std::vector<TraversalStep*>&)> TraversalStrategy;

#endif