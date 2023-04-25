#pragma once

#define FOLD_STEP 0x3f
#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"

#include <vector>
#include <list>

class FoldStep: public TraversalStep {
    public:
        FoldStep();

        using TraversalStep::getInfo;
        virtual std::string getInfo();

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);
};

