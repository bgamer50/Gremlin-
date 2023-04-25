#pragma once

#define COALESCE_STEP 0x40

#include <vector>

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"

class CoalesceStep: public TraversalStep {
    private:
        std::vector<GraphTraversal*> traversals;
    public:
        CoalesceStep(std::vector<GraphTraversal*>& traversals);
        std::vector<GraphTraversal*>& get_traversals();
        virtual void apply(GraphTraversal* parent_traversal, TraverserSet& traversers);
};
