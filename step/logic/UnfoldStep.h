#pragma once

#define UNFOLD_STEP 0x41
#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"

#include <vector>
#include <list>

class UnfoldStep: public TraversalStep {
    public:
        UnfoldStep();

        using TraversalStep::getInfo;
        virtual std::string getInfo();

        // Currently supports list, vector
        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);
};

