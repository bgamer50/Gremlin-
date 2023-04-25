#pragma once

#define UNION_STEP 0x4a

#include <vector>

#include "traversal/GraphTraversal.h"
#include "traversal/Traverser.h"
#include "step/TraversalStep.h"

class UnionStep: public TraversalStep {
    private:
        std::vector<GraphTraversal*> traversals;
    public:
        UnionStep(std::vector<GraphTraversal*>& traversals);
        std::vector<GraphTraversal*>& get_traversals();
        virtual void apply(GraphTraversal* parent_traversal, TraverserSet& traversers);

        using TraversalStep::getInfo;
        virtual std::string getInfo();
};
